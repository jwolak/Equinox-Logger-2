#pragma once

#include <gmock/gmock.h>

#include "IAsyncLogQueueEngine.h"

namespace mocks {
    class AsyncLogQueueEngineMock : public equinox::IAsyncLogQueueEngine {
        MOCK_METHOD(void, processLogMessage, (const std::string& messageToProcess), (override));
        MOCK_METHOD(void, stopWorker, (), (override));
        MOCK_METHOD(void, startWorkerIfNeeded, (), (override));
        MOCK_METHOD(void, setLogsOutputSink, (equinox::logs_output::SINK logsOutputSink), (override));
        MOCK_METHOD(void, flush, (), (override));
    };
}  // namespace mocks