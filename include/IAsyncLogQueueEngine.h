#pragma once

#include <string>

#include "EquinoxLoggerCommon.h"

namespace equinox {
    class IAsyncLogQueueEngine {
        virtual ~IAsyncLogQueueEngine() = default;
        virtual void processLogMessage(const std::string& messageToProcess) = 0;
        virtual void stopWorker() = 0;
        virtual void startWorkerIfNeeded() = 0;
        virtual void setLogsOutputSink(logs_output::SINK logsOutputSink) = 0;
        virtual void flush() = 0;
    };
}  // namespace equinox