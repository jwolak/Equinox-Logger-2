/*
 * EquinoxLoggerEngine.h
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

#ifndef API_EQUINOXLOGGERENGINE_H_
#define API_EQUINOXLOGGERENGINE_H_

#include <memory>
#include <iostream>
#include <string>

#include "EquinoxLoggerCommon.h"

namespace equinox
{

class EquinoxLoggerEngineImpl;

class EQUINOX_API EquinoxLoggerEngine
{
 public:
  static EquinoxLoggerEngine& getInstance();

  EquinoxLoggerEngine(EquinoxLoggerEngine &) = delete;
  EquinoxLoggerEngine(EquinoxLoggerEngine &&) = delete;
  void operator=(const EquinoxLoggerEngine&) = delete;
  void operator=(const EquinoxLoggerEngine&&) = delete;

  template<typename ... Args>
  void log(level::LOG_LEVEL msgLevel, std::string msgFormat, Args &&... args)
  {
    const int nullEndCharacter = 1;
    int numberOfCharacters = std::snprintf(nullptr, 0, msgFormat.c_str(), std::forward<Args>(args) ...) + nullEndCharacter;
    if (numberOfCharacters > 0)
    {
      auto messageBufferSize = static_cast<size_t>(numberOfCharacters);
      auto messageBuffer = std::make_unique<char[]>(messageBufferSize);
      std::snprintf(messageBuffer.get(), messageBufferSize, msgFormat.c_str(), std::forward<Args>(args) ...);
      std::string mFormatedOutpurMessage_ = std::string(messageBuffer.get(), messageBuffer.get() + messageBufferSize - nullEndCharacter);
      processLogMessage(msgLevel, mFormatedOutpurMessage_);
    } else
    {
      std::cout << "[EquinoxLoggerEngine] Message formatting error" << std::endl;
    }
  }

  void setup(equinox::level::LOG_LEVEL logLevel, std::string logPrefix, equinox::logs_output::SINK logsOutputSink, std::string logFileName);
  void changeLevel(level::LOG_LEVEL logLevel);
  void changeLogsOutputSink(logs_output::SINK logsOutputSink);

 protected:
  EquinoxLoggerEngine();

 private:
  std::unique_ptr<EquinoxLoggerEngineImpl> mEquinoxLoggerEngineImpl_;
  void processLogMessage(level::LOG_LEVEL msgLevel, std::string formatedOutputMessage);
};

} /*namespace equinox*/

#endif /* API_EQUINOXLOGGERENGINE_H_ */
