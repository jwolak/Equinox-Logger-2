#pragma once

#include <gmock/gmock.h>

#include "IFileLogsProducer.h"

namespace mocks {
    class FileLogsProducerMock : public equinox::IFileLogsProducer {
        MOCK_METHOD(void, setupFile, (const std::string& logFileName, std::size_t maxLogFileSizeBytes, std::size_t maxLogFiles), (override));
        MOCK_METHOD(void, logMessage, (const std::string& messageToLog), (override));
        MOCK_METHOD(void, flush, (), (override));
    };
}  // namespace mocks