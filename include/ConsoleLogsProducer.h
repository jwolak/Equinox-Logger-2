/*
 * ConsoleLogsProducer.h
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

#ifndef INCLUDE_CONSOLELOGSPRODUCER_H_
#define INCLUDE_CONSOLELOGSPRODUCER_H_

#include <string>
#include <memory>
#include <mutex>

#include "EquinoxLoggerCommon.h"
#include "TimestampProducer.h"

namespace equinox
{

class EQUINOX_API IConsoleLogsProducer
{
 public:
  virtual ~IConsoleLogsProducer() = default;
  virtual void logMessage(std::string) = 0;
};

class EQUINOX_API ConsoleLogsProducer : public IConsoleLogsProducer
{
 public:
  ConsoleLogsProducer(std::shared_ptr<ITimestampProducer> timestampProducer)
  : mMessageBuffer_ {}
  , mMessageBufferAccessLock_ {}
  , mTimestampProducer_ { timestampProducer }
  {
  }

  void logMessage(std::string format) override;

 private:
  std::string mMessageBuffer_;
  std::mutex mMessageBufferAccessLock_;
  std::shared_ptr<ITimestampProducer> mTimestampProducer_;
};

} /*namespace equinox*/

#endif /* INCLUDE_CONSOLELOGSPRODUCER_H_ */
