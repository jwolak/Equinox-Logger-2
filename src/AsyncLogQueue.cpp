/*
 * AsyncLogQueue.cpp
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

#include "AsyncLogQueue.h"

#include <chrono>

namespace equinox
{
    AsyncLogQueue::AsyncLogQueue(size_t queue_max_size)
        : queue_max_size_(queue_max_size), queue_mutex_{}, cv_{}, stop_(false)
    {
    }

    AsyncLogQueue::~AsyncLogQueue() = default;

    void AsyncLogQueue::Enqueue(const std::string &log_message)
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        if (queue_.size() >= queue_max_size_)
        {
            queue_.pop_front(); // Remove the oldest log message to make room for the new one
        }
        queue_.push_back(log_message);
        lock.unlock();
        cv_.notify_one();
    }

    bool AsyncLogQueue::Dequeue(std::vector<std::string> &out, size_t max_batch_size, uint32_t timeout_ms)
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        if (!cv_.wait_for(lock, std::chrono::milliseconds(timeout_ms), [this]()
                          { return !queue_.empty() || stop_; }))
        {
            return true;
        }

        if (stop_ && queue_.empty())
        {
            return false;
        }

        size_t batch_size = std::min(max_batch_size, queue_.size());
        out.reserve(batch_size);
        for (size_t i = 0; i < batch_size; ++i)
        {
            out.push_back(std::move(queue_.front()));
            queue_.pop_front();
        }

        return true;
    }

    void AsyncLogQueue::Stop()
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        stop_ = true;
        lock.unlock();
        cv_.notify_all();
    }
} // namespace equinox