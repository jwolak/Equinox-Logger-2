/*
 * EquinoxLogger-LoggerEngine.h
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
#ifndef INCLUDE_EQUINOXLOGGER_LOGGERENGINE_H_
#define INCLUDE_EQUINOXLOGGER_LOGGERENGINE_H_

#include "EquinoxLogger-LoggerEngineLogic.h"

#include <memory>
#include <string>

namespace equinox {

class EQUINOX_API LoggerEngine
{
     public:
        LoggerEngine()
        : mTimestampProducer { std::make_shared<TimestampProducer>() }
        , mFileLogsProducer { std::make_shared<FileLogsProducer>(mTimestampProducer) }
        , mConsoleLogsProducer { std::make_shared<ConsoleLogsProducer>(mTimestampProducer) }
        , mLogsProducer_ { std::make_shared<LogsProducer>(mFileLogsProducer, mConsoleLogsProducer) }
        , mLoggerEngineLogic_ { std::make_shared<LoggerEngineLogic>(mLogsProducer_) }
        {
        }

        template<typename... Args>
        void logTrace(std::string format, Args &&... args)
        {
          mLoggerEngineLogic_->log(level::LOG_LEVEL::trace, format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void logDebug(std::string format, Args &&... args)
        {
          mLoggerEngineLogic_->log(level::LOG_LEVEL::debug, format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void logInfo(std::string format, Args &&... args)
        {
          mLoggerEngineLogic_->log(level::LOG_LEVEL::info, format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void logWarning(std::string format, Args &&... args)
        {
          mLoggerEngineLogic_->log(level::LOG_LEVEL::warning, format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void logError(std::string format, Args &&... args)
        {
          mLoggerEngineLogic_->log(level::LOG_LEVEL::error, format, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void logCritical(std::string format, Args &&... args)
        {
          mLoggerEngineLogic_->log(level::LOG_LEVEL::critical, format, std::forward<Args>(args)...);
        }

        void setLogLevel(level::LOG_LEVEL logLevel);
        void setBacktrace(size_t numberOfMessages);
        void setLogsOutputSink(logs_output::SINK logsOutputSink);

     private:
        std::shared_ptr<ITimestampProducer> mTimestampProducer;
        std::shared_ptr<FileLogsProducer> mFileLogsProducer;
        std::shared_ptr<ConsoleLogsProducer> mConsoleLogsProducer;
        std::shared_ptr<LogsProducer> mLogsProducer_;
        std::shared_ptr<LoggerEngineLogic> mLoggerEngineLogic_;

};

} /*namespace equinox*/

#endif /* INCLUDE_EQUINOXLOGGER_LOGGERENGINE_H_ */
