/*
 * EquinoxLoggerEngineImpl.cpp
 *
 *  Created on: 2023
 *      Author: Janusz Wolak
 */

/*-
 * BSD 3-Clause License
 *
 * Copyright (c) 2023, Janusz Wolak
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

#include "EquinoxLoggerEngineImpl.h"

#include <vector>

equinox::EquinoxLoggerEngineImpl::~EquinoxLoggerEngineImpl()
{
  stopWorker();
}

void equinox::EquinoxLoggerEngineImpl::startWorkerIfNeeded()
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
        break;
      }

      std::lock_guard<std::mutex> lock(mWorkerMutex_);
      for (const auto &message : batch)
      {
        dispatchMessage(message);
      }
    } });
}

void equinox::EquinoxLoggerEngineImpl::stopWorker()
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

void equinox::EquinoxLoggerEngineImpl::dispatchMessage(const std::string &messageToLog)
{
  switch (mLogsOutputSink_)
  {
  case logs_output::SINK::console:
    mConsoleLogsProducer_->logMessage(messageToLog);
    break;

  case logs_output::SINK::file:
    mFileLogsProducer_->logMessage(messageToLog);
    break;

  case logs_output::SINK::console_and_file:
    mConsoleLogsProducer_->logMessage(messageToLog);
    mFileLogsProducer_->logMessage(messageToLog);
    break;
  }
}

void equinox::EquinoxLoggerEngineImpl::logMessage(level::LOG_LEVEL msgLevel, const std::string &formatedOutputMessage)
{
  if ((msgLevel != level::LOG_LEVEL::off) and (msgLevel >= mLogLevel_))
  {
    mOutputMessage_.clear();

    switch (msgLevel)
    {
    case level::LOG_LEVEL::critical:
      mOutputMessage_ = mLogPrefix_ + std::string("[CRITICAL] ") + formatedOutputMessage;
      break;

    case level::LOG_LEVEL::debug:
      mOutputMessage_ = mLogPrefix_ + std::string("[DEBUG] ") + formatedOutputMessage;
      break;

    case level::LOG_LEVEL::error:
      mOutputMessage_ = mLogPrefix_ + std::string("[ERROR] ") + formatedOutputMessage;
      break;

    case level::LOG_LEVEL::info:
      mOutputMessage_ = mLogPrefix_ + std::string("[INFO] ") + formatedOutputMessage;
      break;

    case level::LOG_LEVEL::trace:
      mOutputMessage_ = mLogPrefix_ + std::string("[TRACE] ") + formatedOutputMessage;
      break;

    case level::LOG_LEVEL::warning:
      mOutputMessage_ = mLogPrefix_ + std::string("[WARNING] ") + formatedOutputMessage;
      break;
    }

    startWorkerIfNeeded();
    mAsyncQueue_.Enqueue(mOutputMessage_);
  }
}

void equinox::EquinoxLoggerEngineImpl::setup(level::LOG_LEVEL logLevel, const std::string &logPrefix, logs_output::SINK logsOutputSink,
                                             const std::string &logFileName, std::size_t maxLogFileSizeBytes, std::size_t maxLogFiles)
{
  mLogLevel_ = logLevel;
  mLogPrefix_ = std::string("[" + logPrefix + "]");
  {
    std::lock_guard<std::mutex> lock(mWorkerMutex_);
    mLogsOutputSink_ = logsOutputSink;
  }
  mLogFileName_ = logFileName;
  mMaxLogFileSizeBytes_ = maxLogFileSizeBytes;
  mMaxLogFiles_ = maxLogFiles;

  {
    std::lock_guard<std::mutex> lock(mWorkerMutex_);
    if (equinox::logs_output::SINK::file == logsOutputSink or equinox::logs_output::SINK::console_and_file == logsOutputSink)
    {
      mFileLogsProducer_->setupFile(mLogFileName_, mMaxLogFileSizeBytes_, mMaxLogFiles_);
    }
  }

  startWorkerIfNeeded();
}

void equinox::EquinoxLoggerEngineImpl::changeLevel(level::LOG_LEVEL logLevel)
{
  mLogLevel_ = logLevel;
}

void equinox::EquinoxLoggerEngineImpl::changeLogsOutputSink(logs_output::SINK logsOutputSink)
{
  {
    std::lock_guard<std::mutex> lock(mWorkerMutex_);
    mLogsOutputSink_ = logsOutputSink;

    if (equinox::logs_output::SINK::file == logsOutputSink or equinox::logs_output::SINK::console_and_file == logsOutputSink)
    {
      mFileLogsProducer_->setupFile(mLogFileName_, mMaxLogFileSizeBytes_, mMaxLogFiles_);
    }
  }
}
