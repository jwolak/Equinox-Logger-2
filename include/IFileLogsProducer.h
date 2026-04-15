#pragma once

#include <string>

#include "EquinoxLoggerCommon.h"

namespace equinox {

    class EQUINOX_API IFileLogsProducer {
       public:
        virtual ~IFileLogsProducer() = default;
        virtual void setupFile(const std::string& logFileName, std::size_t maxLogFileSizeBytes, std::size_t maxLogFiles) = 0;
        virtual void logMessage(const std::string& messageToLog) = 0;
        virtual void flush() = 0;
    };
}  // namespace equinox