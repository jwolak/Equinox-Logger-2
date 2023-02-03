/*
 * LogsProducerTests.cpp
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

#include <memory>
#include <iostream>
#include <string>

#include <gtest/gtest.h>

#include "EquinoxLogger-LogsProducer.h"
#include "FileLogsProducerMock.h"
#include "ConsoleLogsProducerMock.h"

namespace logs_producer_tests
{

using ::testing::Return;
using ::testing::_;

namespace
{
const equinox::logs_output::SINK kSinkConsole = equinox::logs_output::SINK::console;
const equinox::logs_output::SINK kSinkFile = equinox::logs_output::SINK::file;
const equinox::logs_output::SINK kSinkConsoleAndFile = equinox::logs_output::SINK::console_and_file;
const std::string kTestLogMessage = std::string("Test log");
}

class LogsProducerTests : public ::testing::Test
{
 public:
  LogsProducerTests()
  : mFileLogsProducerMock { std::make_shared<equinox_mocks::FileLogsProducerMock>() }
  , mConsoleLogsProducerMock { std::make_shared<equinox_mocks::ConsoleLogsProducerMock>() }
  , mLogsProducer { mFileLogsProducerMock, mConsoleLogsProducerMock }
  {
  }

  std::shared_ptr<equinox_mocks::FileLogsProducerMock> mFileLogsProducerMock;
  std::shared_ptr<equinox_mocks::ConsoleLogsProducerMock> mConsoleLogsProducerMock;
  equinox::LogsProducer mLogsProducer;
};

TEST_F(LogsProducerTests, Set_LogsOutputSink_To_Console_And_mSink_Field_Is_Set_To_Console)
{
  mLogsProducer.setLogsOutputSink(kSinkConsole);
  ASSERT_EQ(kSinkConsole, mLogsProducer.mSink);
}

TEST_F(LogsProducerTests, Set_LogsOutputSink_To_File_And_mSink_Field_Is_Set_To_File)
{
  mLogsProducer.setLogsOutputSink(kSinkFile);
  ASSERT_EQ(kSinkFile, mLogsProducer.mSink);
}

TEST_F(LogsProducerTests, Set_LogsOutputSink_To_ConsoleAndFile_And_mSink_Field_Is_Set_To_ConsoleAndFile)
{
  mLogsProducer.setLogsOutputSink(kSinkConsoleAndFile);
  ASSERT_EQ(kSinkConsoleAndFile, mLogsProducer.mSink);
}

TEST_F(LogsProducerTests, Set_OutputSink_To_Console_And_ConsoleLogsProducer_LogMessage_Called)
{
  mLogsProducer.mSink = kSinkConsole;
  EXPECT_CALL(*mConsoleLogsProducerMock, LogMessage(_)).Times(1);
  mLogsProducer.LogMessage(kTestLogMessage);
}

TEST_F(LogsProducerTests, Set_OutputSink_To_File_And_FileLogsProducer_LogMessage_Called)
{
  mLogsProducer.mSink = kSinkFile;
  EXPECT_CALL(*mFileLogsProducerMock, LogMessage(_)).Times(1);
  mLogsProducer.LogMessage(kTestLogMessage);
}

TEST_F(LogsProducerTests, Set_OutputSink_To_ConsoleAndFile_And_FileLogsProducer_And_ConsoleLogsProducer_LogMessage_Called)
{
  mLogsProducer.mSink = kSinkConsoleAndFile;
  EXPECT_CALL(*mConsoleLogsProducerMock, LogMessage(_)).Times(1);
  EXPECT_CALL(*mFileLogsProducerMock, LogMessage(_)).Times(1);
  mLogsProducer.LogMessage(kTestLogMessage);
}

} /*namespace logs_producer_tests*/
