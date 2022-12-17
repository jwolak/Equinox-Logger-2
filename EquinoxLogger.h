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

template<typename T>
inline void trace(const T &logMessage)
{
}

template<typename T>
inline void debug(const T &logMessage)
{
}

template<typename T>
inline void info(const T &logMessage)
{
}

template<typename T>
inline void warn(const T &logMessage)
{
}

template<typename T>
inline void error(const T &logMessage)
{
}

template<typename T>
inline void critical(const T &logMessage)
{
}

template<typename... Args>
inline void trace(Args& ... args)
{
}

template<typename... Args>
inline void debug(Args& ... args)
{
}

template<typename... Args>
inline void info(Args& ... args)
{
}

template<typename... Args>
inline void warn(Args& ... args)
{
}

template<typename... Args>
inline void error(Args& ... args)
{
}

template<typename... Args>
inline void critical(Args& ... args)
{
}

EQUINOX_INLINE void setLevel(level::LOG_LEVEL logLevel)
{
}

EQUINOX_INLINE void setBacktrace(size_t numberOfMessages)
{
}

EQUINOX_INLINE void setLogsOutputSink(logs_output::SINK logsOutputSink)
{
}

} /*namespace equinox*/

#endif /* EQUINOXLOGGER_H_ */
