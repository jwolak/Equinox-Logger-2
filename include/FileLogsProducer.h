/*
 * FileLogsProducer.h
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

#ifndef INCLUDE_FILELOGSPRODUCER_H_
#define INCLUDE_FILELOGSPRODUCER_H_

#include <cstddef>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>
#include <mutex>

#include "EquinoxLoggerCommon.h"
#include "TimestampProducer.h"

namespace equinox
{

  class EQUINOX_API IFileLogsProducer
  {
  public:
    virtual ~IFileLogsProducer() = default;
    virtual void setupFile(const std::string &logFileName, std::size_t maxLogFileSizeBytes, std::size_t maxLogFiles) = 0;
    virtual void logMessage(const std::string &messageToLog) = 0;
  };

  class EQUINOX_API FileLogsProducer : public IFileLogsProducer
  {
  public:
    FileLogsProducer(std::shared_ptr<ITimestampProducer> timestampProducer)
        : mMessageBuffer_{}, mMessageBufferAccessLock_{}, mTimestampProducer{timestampProducer}, mFdLogFile_{}, mLogFileName_{}, mMaxLogFileSizeBytes_{0U}, mMaxLogFiles_{0U}, mNextRotationIndex_{1U}
    {
    }

    ~FileLogsProducer() noexcept
    {
      if (mFdLogFile_.is_open())
      {
        try
        {
          mFdLogFile_.close();
        }
        catch (std::ofstream::failure &ex)
        {
          // Destructor - cannot propagate exception
          std::cerr << "[EquinoxLogger] Warning: Failed to close log file in destructor: "
                    << ex.what() << std::endl;
        }
      }
    }

    FileLogsProducer(const FileLogsProducer &) = delete;
    FileLogsProducer(const FileLogsProducer &&) = delete;
    FileLogsProducer &operator=(FileLogsProducer &) = delete;

    void setupFile(const std::string &logFileName, std::size_t maxLogFileSizeBytes, std::size_t maxLogFiles) override;
    void logMessage(const std::string &messageToLog) override;

  private:
    void openLogFileAppend();
    void openLogFileTruncate();
    void rotateIfNeeded();
    std::string buildRotatedFileName(std::size_t index) const;
    bool isRotationEnabled() const;

    std::string mMessageBuffer_;
    std::mutex mMessageBufferAccessLock_;
    std::shared_ptr<ITimestampProducer> mTimestampProducer;
    std::ofstream mFdLogFile_;
    std::string mLogFileName_;
    std::size_t mMaxLogFileSizeBytes_;
    std::size_t mMaxLogFiles_;
    std::size_t mNextRotationIndex_;
  };
} /*namespace equinox*/

#endif /* INCLUDE_FILELOGSPRODUCER_H_ */
