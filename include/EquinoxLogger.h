/*
 * EquinoxLogger.h
 *
 * Copylefts (C) 2022
 * Author: Janusz Wolak

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef EQUINOXLOGGER_H_
#define EQUINOXLOGGER_H_

#include "EquinoxLogger-Common.h"
#include "EquinoxLogger-LoggerEngine.h"

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

void setup(level::LOG_LEVEL logLevel, std::string logPrefix, logs_output::SINK logsOutputSink, std::string logFileName = kLogFileName);

void changeLevel(level::LOG_LEVEL logLevel);

void changeLogsOutputSink(logs_output::SINK logsOutputSink);

} /*namespace equinox*/

#define SETUP(logLevel, logPrefix, logsOutputSink, logFileName) equinox::LoggerEngine::getInstance().setup(logLevel, logPrefix, logsOutputSink, logFileName)
#define LOG_TRACE(format, ...)     equinox::LoggerEngine::getInstance().log(equinox::level::LOG_LEVEL::trace, format, __VA_ARGS__)
#define LOG_DEBUG(format, ...)     equinox::LoggerEngine::getInstance().log(equinox::level::LOG_LEVEL::debug, format, __VA_ARGS__)
#define LOG_INFO(format, ...)      equinox::LoggerEngine::getInstance().log(equinox::level::LOG_LEVEL::info, format, __VA_ARGS__)
#define LOG_WARNING(format, ...)   equinox::LoggerEngine::getInstance().log(equinox::level::LOG_LEVEL::warning, format, __VA_ARGS__)
#define LOG_ERROR(format, ...)     equinox::LoggerEngine::getInstance().log(equinox::level::LOG_LEVEL::error, format, __VA_ARGS__)
#define LOG_CRITICAL(format, ...)  equinox::LoggerEngine::getInstance().log(equinox::level::LOG_LEVEL::critical, format, __VA_ARGS__)

#define CHANGE_LOG_LEVEL(level)    equinox::LoggerEngine::getInstance().setLogLevel(level);
#define CHANGE_OUTPUT_SINK(sink)   equinox::LoggerEngine::getInstance().setLogsOutputSink(sink);

#endif /* EQUINOXLOGGER_H_ */
