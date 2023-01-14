/*
 * EquinoxLogger-LoggerEngineLogic.h
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
#ifndef INCLUDE_EQUINOXLOGGER_LOGGERENGINELOGIC_H_
#define INCLUDE_EQUINOXLOGGER_LOGGERENGINELOGIC_H_

#include <string>

#include <chrono>
#include <cstring>
#include <iostream>

#include <stddef.h>

#include "EquinoxLogger-Common.h"
#include "EquinoxLogger-ConsoleLogsProducer.h"
#include "EquinoxLogger-FileLogsProducer.h"

namespace equinox
{

class EQUINOX_API LoggerEngineLogic
{
 public:
  LoggerEngineLogic()
  : mLogLevel { level::LOG_LEVEL::critical }
  , mSink { logs_output::SINK::console }
  , mConsoleLogsProducer {}
  , mFileLogsProducer {}
  {
  }

  template<typename... Args>
  void log(level::LOG_LEVEL level, std::string format, Args &&... args)
  {
/*    std::string formatAsString = "[%s] ";
    formatAsString += format;
    formatAsString += "\n";
    const time_t currentTime = std::chrono::system_clock::system_clock::to_time_t(std::chrono::system_clock::system_clock::now());
    printf(formatAsString.c_str(), strtok(ctime(&currentTime), "\n"), args...);*/

    if (mLogLevel >= level)
    {
      switch (mSink)
      {
        case logs_output::SINK::console:
          mConsoleLogsProducer.LogMessage(level, format, std::forward<Args>(args)...);
          break;

        case logs_output::SINK::file:
          mFileLogsProducer.LogMessage(level, format, std::forward<Args>(args)...);
          break;

        case logs_output::SINK::console_and_file:
          mConsoleLogsProducer.LogMessage(level, format, std::forward<Args>(args)...);
          mFileLogsProducer.LogMessage(level, format, std::forward<Args>(args)...);
          break;
      }
    }
  }

  void setLogLevel(level::LOG_LEVEL logLevel);
  void setBacktrace(size_t numberOfMessages);
  void setLogsOutputSink(logs_output::SINK logsOutputSink);

  level::LOG_LEVEL mLogLevel;
  logs_output::SINK mSink;
  ConsoleLogsProducer mConsoleLogsProducer;
  FileLogsProducer mFileLogsProducer;
};

} /*namespace equinox*/

#endif /* INCLUDE_EQUINOXLOGGER_LOGGERENGINELOGIC_H_ */
