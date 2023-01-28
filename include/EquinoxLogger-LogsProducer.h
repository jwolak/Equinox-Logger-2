/*
 * EquinoxLogger-LogsProducer.h
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

#ifndef INCLUDE_EQUINOXLOGGER_LOGSPRODUCER_H_
#define INCLUDE_EQUINOXLOGGER_LOGSPRODUCER_H_

#include <string>
#include <memory>

#include "EquinoxLogger-Common.h"
#include "EquinoxLogger-FileLogsProducer.h"
#include "EquinoxLogger-ConsoleLogsProducer.h"

namespace equinox
{

class EQUINOX_API ILogsProducer
{
 public:
  virtual ~ILogsProducer() = default;
  virtual void LogMessage(std::string) = 0;
  virtual void setLogsOutputSink(logs_output::SINK) = 0;
};

class EQUINOX_API LogsProducer : public ILogsProducer
{
 public:
  LogsProducer(std::shared_ptr<IFileLogsProducer> fileLogsProducer,
               std::shared_ptr<IConsoleLogsProducer> consoleLogsProducer)
  : mSink { logs_output::SINK::console }
  , mFileLogsProducer { fileLogsProducer }
  , mConsoleLogsProducer { consoleLogsProducer }
  {
  }

  void LogMessage(std::string messageToLog) override;
  void setLogsOutputSink(logs_output::SINK logsOutputSink) override;

  logs_output::SINK mSink;

 private:
  std::shared_ptr<IFileLogsProducer> mFileLogsProducer;
  std::shared_ptr<IConsoleLogsProducer> mConsoleLogsProducer;
};

} /*namespace equinox*/

#endif /* INCLUDE_EQUINOXLOGGER_LOGSPRODUCER_H_ */
