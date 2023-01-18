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
#include <memory>
#include <string>
#include <stdexcept>
#include <stddef.h>

#include "EquinoxLogger-Common.h"
#include "EquinoxLogger-TimestampProducer.h"
#include "EquinoxLogger-ConsoleLogsProducer.h"
#include "EquinoxLogger-FileLogsProducer.h"

#include "EquinoxLogger-LogsProducer.h"

namespace equinox
{

class EQUINOX_API LoggerEngineLogic
{
 public:
  LoggerEngineLogic(std::shared_ptr<LogsProducer> logsProducer)
  : mLogLevel { level::LOG_LEVEL::critical }
  , mLogsProducer_ { logsProducer }
  {
  }

  template<typename... Args>
  void log(level::LOG_LEVEL level, std::string format, Args &&... args)
  {

    if (level >= mLogLevel && level != level::LOG_LEVEL::off)
    {
      int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1;
      if (size_s <= 0)
      {
        throw std::runtime_error("Error during formatting.");
      }
      auto size = static_cast<size_t>(size_s);
      std::unique_ptr<char[]> buf(new char[size]);
      std::snprintf(buf.get(), size, format.c_str(), args ...);
      std::string tmp(buf.get(), buf.get() + size - 1);

      switch(level)
      {
        case level::LOG_LEVEL::critical:
          tmp = "[critical] " + tmp;
          break;

        case level::LOG_LEVEL::debug:
          tmp = "[debug] " + tmp;
          break;

        case level::LOG_LEVEL::error:
          tmp = "[error] " + tmp;
          break;

        case level::LOG_LEVEL::info:
          tmp = "[info] " + tmp;
          break;

        case level::LOG_LEVEL::trace:
          tmp = "[trace] " + tmp;
          break;

        case level::LOG_LEVEL::warning:
          tmp = "[warning] " + tmp;
          break;
      }
      mLogsProducer_->LogMessage(tmp);
    }

  }

  void setLogLevel(level::LOG_LEVEL logLevel);
  void setBacktrace(size_t numberOfMessages);
  void setLogsOutputSink(logs_output::SINK logsOutputSink);

  level::LOG_LEVEL mLogLevel;

 private:
  std::shared_ptr<LogsProducer> mLogsProducer_;
};

} /*namespace equinox*/

#endif /* INCLUDE_EQUINOXLOGGER_LOGGERENGINELOGIC_H_ */
