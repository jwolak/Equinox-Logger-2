#pragma once

#include <string>

#include "EquinoxLoggerCommon.h"

namespace equinox {
    class IEquinoxLoggerEngineImpl {
       public:
        virtual ~IEquinoxLoggerEngineImpl() = default;

        virtual void logMessage(level::LOG_LEVEL msgLevel, const std::string& formatedOutputMessage) = 0;
        virtual bool setup(level::LOG_LEVEL logLevel, const std::string& logPrefix, logs_output::SINK logsOutputSink, const std::string& logFileName,
                           std::size_t maxLogFileSizeBytes, std::size_t maxLogFiles) = 0;
        virtual void changeLevel(level::LOG_LEVEL logLevel) = 0;
        virtual bool changeLogsOutputSink(logs_output::SINK logsOutputSink) = 0;
        virtual void flush() = 0;
    };
}  // namespace equinox