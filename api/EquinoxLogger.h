/*
 * EquinoxLogger.h
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

#ifndef API_EQUINOXLOGGER_H_
#define API_EQUINOXLOGGER_H_

#include "EquinoxLoggerCommon.h"
#include "EquinoxLoggerEngine.h"

namespace equinox {

template<typename... Args>
inline void trace(std::string format, Args&& ... args)
{
  equinox::LoggerEngine::getInstance().log(level::LOG_LEVEL::trace, format, std::forward<Args>(args)...);
}

template<typename... Args>
inline void debug(std::string format, Args&& ... args)
{
  equinox::LoggerEngine::getInstance().log(level::LOG_LEVEL::debug, format, std::forward<Args>(args)...);
}

template<typename... Args>
inline void info(std::string format, Args&& ... args)
{
  equinox::LoggerEngine::getInstance().log(level::LOG_LEVEL::info, format, std::forward<Args>(args)...);
}

template<typename... Args>
inline void warning(std::string format, Args&& ... args)
{
  equinox::LoggerEngine::getInstance().log(level::LOG_LEVEL::warning, format, std::forward<Args>(args)...);
}

template<typename... Args>
inline void error(std::string format, Args&& ... args)
{
  equinox::LoggerEngine::getInstance().log(level::LOG_LEVEL::error, format, std::forward<Args>(args)...);
}

template<typename... Args>
inline void critical(std::string format, Args&& ... args)
{
  equinox::LoggerEngine::getInstance().log(level::LOG_LEVEL::critical, format, std::forward<Args>(args)...);
}

EQUINOX_API EQUINOX_INLINE void setup(level::LOG_LEVEL logLevel, std::string logPrefix, logs_output::SINK logsOutputSink, std::string logFileName = kLogFileName);

EQUINOX_API EQUINOX_INLINE void changeLevel(level::LOG_LEVEL logLevel);

EQUINOX_API EQUINOX_INLINE void changeLogsOutputSink(logs_output::SINK logsOutputSink);

} /*namespace equinox*/

#endif /* API_EQUINOXLOGGER_H_ */
