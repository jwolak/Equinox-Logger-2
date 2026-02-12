/*
 * AsyncLogQueueEngine.cpp
 *
 *  Created on: 2026
 *      Author: Janusz Wolak
 */

/*-
 * BSD 3-Clause License
 *
 * Copyright (c) 2026, Janusz Wolak
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#include "AsyncLogQueueEngine.h"

namespace equinox
{

    namespace
    {
        static constexpr std::size_t kDefaultQueueMaxSize = 10000U;
        static constexpr std::size_t kDefaultBatchSize = 64U;
        static constexpr uint32_t kDefaultDequeueTimeoutMs = 50U;
    }

    AsyncLogQueueEngine::AsyncLogQueueEngine(IConsoleLogsProducer &consoleLogsProducer, IFileLogsProducer &fileLogsProducer, logs_output::SINK logsOutputSink)
        : mAsyncQueue_(kDefaultQueueMaxSize), mWorkerThread_{}, mWorkerRunning_(false), mWorkerMutex_{}, mConsoleLogsProducer_(consoleLogsProducer), mFileLogsProducer_(fileLogsProducer), mLogsOutputSink_(logsOutputSink)
    {
    }

    AsyncLogQueueEngine::~AsyncLogQueueEngine()
    {
        stopWorker();
    }

    void AsyncLogQueueEngine::processLogMessage(const std::string &messageToProcess)
    {
        mAsyncQueue_.Enqueue(messageToProcess);
    }

    void AsyncLogQueueEngine::startWorkerIfNeeded()
    {
        bool expected = false;
        if (!mWorkerRunning_.compare_exchange_strong(expected, true))
        {
            return;
        }

        mWorkerThread_ = std::thread([this]()
                                     {
            std::vector<std::string> batch;
            while (true)
            {
                batch.clear();
                if (!mAsyncQueue_.Dequeue(batch, kDefaultBatchSize, kDefaultDequeueTimeoutMs))
                {
                    if (!mWorkerRunning_.load())
                    {
                        break;
                    }
                    continue;
                }

                for (const auto &message : batch)
                {
                    dispatchMessage(message);
                }
            } });
    }

    void AsyncLogQueueEngine::stopWorker()
    {
        if (!mWorkerRunning_.exchange(false))
        {
            return;
        }

        mAsyncQueue_.Stop();
        if (mWorkerThread_.joinable())
        {
            mWorkerThread_.join();
        }
    }

    void AsyncLogQueueEngine::dispatchMessage(const std::string &messageToLog)
    {
        std::lock_guard<std::mutex> lock(mWorkerMutex_);
        switch (mLogsOutputSink_)
        {
        case logs_output::SINK::console:
            mConsoleLogsProducer_.logMessage(messageToLog);
            break;

        case logs_output::SINK::file:
            mFileLogsProducer_.logMessage(messageToLog);
            break;

        case logs_output::SINK::console_and_file:
            mConsoleLogsProducer_.logMessage(messageToLog);
            mFileLogsProducer_.logMessage(messageToLog);
            break;
        }
    }

    void AsyncLogQueueEngine::setLogsOutputSink(logs_output::SINK logsOutputSink)
    {
        std::lock_guard<std::mutex> lock(mWorkerMutex_);
        mLogsOutputSink_ = logsOutputSink;
    }

    void AsyncLogQueueEngine::flush()
    {
        std::lock_guard<std::mutex> lock(mWorkerMutex_);
        mConsoleLogsProducer_.flush();
        mFileLogsProducer_.flush();
    }
} // namespace equinox