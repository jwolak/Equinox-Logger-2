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
  LoggerEngineLogic(std::shared_ptr<ILogsProducer> logsProducer)
  : mLogLevel_ { level::LOG_LEVEL::critical }
  , mFormatedOutpurMessage_ {}
  , mLogsProducer_ { logsProducer }
  {
  }

  template<typename ... Args>
  void log(level::LOG_LEVEL msgLevel, std::string msgFormat, Args &&... args)
  {
    if (msgLevel != level::LOG_LEVEL::off && msgLevel >= mLogLevel_)
    {
      const int nullEndCharacter = 1;
      int numberOfCharacters = std::snprintf(nullptr, 0, msgFormat.c_str(), std::forward<Args>(args) ...) + nullEndCharacter;
      if (numberOfCharacters > 0)
      {
        auto messageBufferSize = static_cast<size_t>(numberOfCharacters);
        auto messageBuffer = std::make_unique<char[]>(messageBufferSize);
        std::snprintf(messageBuffer.get(), messageBufferSize, msgFormat.c_str(), std::forward<Args>(args)  ...);
        mFormatedOutpurMessage_ = std::string(messageBuffer.get(), messageBuffer.get() + messageBufferSize - nullEndCharacter);

        switch (msgLevel)
        {
          case level::LOG_LEVEL::critical:
            mFormatedOutpurMessage_ = kCriticalPrefix + mFormatedOutpurMessage_;
            break;

          case level::LOG_LEVEL::debug:
            mFormatedOutpurMessage_ = kDebugPrefix + mFormatedOutpurMessage_;
            break;

          case level::LOG_LEVEL::error:
            mFormatedOutpurMessage_ = kErrorPrefix + mFormatedOutpurMessage_;
            break;

          case level::LOG_LEVEL::info:
            mFormatedOutpurMessage_ = kInfoPrefix + mFormatedOutpurMessage_;
            break;

          case level::LOG_LEVEL::trace:
            mFormatedOutpurMessage_ = kTracePrefix + mFormatedOutpurMessage_;
            break;

          case level::LOG_LEVEL::warning:
            mFormatedOutpurMessage_ = kWarningPrefix + mFormatedOutpurMessage_;
            break;
        }
        mLogsProducer_->LogMessage(mFormatedOutpurMessage_);
      }
      else
      {
        std::cout << "[LoggerEngineLogic] Message formatting error" << std::endl;
      }
    }

  }

  void setLogLevel(level::LOG_LEVEL logLevel);
  void setLogsOutputSink(logs_output::SINK logsOutputSink);

  level::LOG_LEVEL mLogLevel_;
  std::string mFormatedOutpurMessage_;

 private:
  std::shared_ptr<ILogsProducer> mLogsProducer_;
};

} /*namespace equinox*/

#endif /* INCLUDE_EQUINOXLOGGER_LOGGERENGINELOGIC_H_ */
