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
#include "EquinoxLogger-LoggerManager.h"

namespace equinox {

template<typename... Args>
inline void trace(std::string format, Args&& ... args)
{
  equinox::LoggerManager::getLoggerManagerInstance()->getLoggerEngine()->logTrace(format, std::forward<Args>(args)...);
}

template<typename... Args>
inline void debug(std::string format, Args&& ... args)
{
  equinox::LoggerManager::getLoggerManagerInstance()->getLoggerEngine()->logDebug(format, std::forward<Args>(args)...);
}

template<typename... Args>
inline void info(std::string format, Args&& ... args)
{
  equinox::LoggerManager::getLoggerManagerInstance()->getLoggerEngine()->logInfo(format, std::forward<Args>(args)...);
}

template<typename... Args>
inline void warning(std::string format, Args&& ... args)
{
  equinox::LoggerManager::getLoggerManagerInstance()->getLoggerEngine()->logWarning(format, std::forward<Args>(args)...);
}

template<typename... Args>
inline void error(std::string format, Args&& ... args)
{
  equinox::LoggerManager::getLoggerManagerInstance()->getLoggerEngine()->logError(format, std::forward<Args>(args)...);
}

template<typename... Args>
inline void critical(std::string format, Args&& ... args)
{
  equinox::LoggerManager::getLoggerManagerInstance()->getLoggerEngine()->logCritical(format, std::forward<Args>(args)...);
}

EQUINOX_INLINE void setLevel(level::LOG_LEVEL logLevel)
{
  equinox::LoggerManager::getLoggerManagerInstance()->getLoggerEngine()->setLogLevel(logLevel);
}

EQUINOX_INLINE void setLogsOutputSink(logs_output::SINK logsOutputSink)
{
  equinox::LoggerManager::getLoggerManagerInstance()->getLoggerEngine()->setLogsOutputSink(logsOutputSink);
}

} /*namespace equinox*/

#define LOG_TRACE(format, ...)     equinox::LoggerManager::getLoggerManagerInstance()->getLoggerEngine()->logTrace(format, __VA_ARGS__);
#define LOG_DEBUG(format, ...)     equinox::LoggerManager::getLoggerManagerInstance()->getLoggerEngine()->logDebug(format, __VA_ARGS__);
#define LOG_INFO(format, ...)      equinox::LoggerManager::getLoggerManagerInstance()->getLoggerEngine()->logInfo(format, __VA_ARGS__);
#define LOG_WARNING(format, ...)   equinox::LoggerManager::getLoggerManagerInstance()->getLoggerEngine()->logWarning(format, __VA_ARGS__);
#define LOG_ERROR(format, ...)     equinox::LoggerManager::getLoggerManagerInstance()->getLoggerEngine()->logError(format, __VA_ARGS__);
#define LOG_CRITICAL(format, ...)  equinox::LoggerManager::getLoggerManagerInstance()->getLoggerEngine()->logCritical(format, __VA_ARGS__);

#define SET_LOG_LEVEL(level)       equinox::LoggerManager::getLoggerManagerInstance()->getLoggerEngine()->setLogLevel(level);
#define SET_BACKTRACE(num_of_msgs) equinox::LoggerManager::getLoggerManagerInstance()->getLoggerEngine()->setBacktrace(num_of_msgs);
#define SET_OUTPUT_SINK(sink)      equinox::LoggerManager::getLoggerManagerInstance()->getLoggerEngine()->setLogsOutputSink(sink);

#endif /* EQUINOXLOGGER_H_ */
