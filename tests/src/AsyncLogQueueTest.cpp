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

#include <thread>

#include <gtest/gtest.h>

#include "AsyncLogQueue.h"

namespace async_log_queue_test
{
    namespace
    {
        constexpr size_t kTestQueueMaxSize = 10;
        constexpr const char *testMessage = "Test log message";
    }

    class AsyncLogQueueForTests : public ::equinox::AsyncLogQueue
    {
    public:
        explicit AsyncLogQueueForTests(size_t queue_max_size) : AsyncLogQueue(queue_max_size) {}

        const std::deque<std::string> &getInternalQueue() { return getLogMessagesQueue(); }
    };

    class AsyncLogQueueTest : public ::testing::Test
    {
    public:
        AsyncLogQueueTest() : asyncLogQueue{kTestQueueMaxSize} {}

        AsyncLogQueueForTests asyncLogQueue;
    };

    TEST_F(AsyncLogQueueTest, Queue_Is_Full_And_Oldest_Message_Is_Removed)
    {
        for (size_t i = 0; i < kTestQueueMaxSize; ++i)
        {
            asyncLogQueue.enqueue("Log message " + std::to_string(i));
        }
        ASSERT_EQ(asyncLogQueue.getInternalQueue().size(), kTestQueueMaxSize);
        asyncLogQueue.enqueue(testMessage);

        ASSERT_EQ(asyncLogQueue.getInternalQueue().size(), kTestQueueMaxSize);
    }

    TEST_F(AsyncLogQueueTest, Queue_Is_Empty_And_After_Enqueue_Size_Is_One)
    {
        ASSERT_EQ(asyncLogQueue.getInternalQueue().size(), 0);
        asyncLogQueue.enqueue(testMessage);

        ASSERT_EQ(asyncLogQueue.getInternalQueue().size(), 1);
    }

    TEST_F(AsyncLogQueueTest, Run_Enqueue_From_Two_Thread_And_Queue_Size_Is_Correct)
    {
        std::thread t1([this]()
                       {
                           for (size_t i = 0; i < kTestQueueMaxSize / 2; ++i)
                           {
                               asyncLogQueue.enqueue("Thread 1 - Log message " + std::to_string(i));
                           } });

        std::thread t2([this]()
                       {
                           for (size_t i = 0; i < kTestQueueMaxSize / 2; ++i)
                           {
                               asyncLogQueue.enqueue("Thread 2 - Log message " + std::to_string(i));
                           } });

        t1.join();
        t2.join();

        ASSERT_EQ(asyncLogQueue.getInternalQueue().size(), kTestQueueMaxSize);
    }

    TEST_F(AsyncLogQueueTest, Run_Enqueue_From_Two_Thread_And_Messages_Are_Correctly_Added_To_Queue)
    {

        std::thread t1([this]()
                       {
                           for (size_t i = 0; i < kTestQueueMaxSize / 2; ++i)
                           {
                               asyncLogQueue.enqueue("Thread 1 - Log message " + std::to_string(i));
                           } });

        std::thread t2([this]()
                       {
                           for (size_t i = 0; i < kTestQueueMaxSize / 2; ++i)
                           {
                               asyncLogQueue.enqueue("Thread 2 - Log message " + std::to_string(i));
                           } });

        t1.join();
        t2.join();

        const auto &queue = asyncLogQueue.getInternalQueue();
        for (size_t i = 0; i < kTestQueueMaxSize / 2; ++i)
        {
            ASSERT_TRUE(std::find(queue.begin(), queue.end(), "Thread 1 - Log message " + std::to_string(i)) != queue.end());
            ASSERT_TRUE(std::find(queue.begin(), queue.end(), "Thread 2 - Log message " + std::to_string(i)) != queue.end());
        }
    }
}