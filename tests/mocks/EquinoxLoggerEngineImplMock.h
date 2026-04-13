#pragma once

#include <gmock/gmock.h>

#include "IEquinoxLoggerEngineImpl.h"

namespace mocks {
    class EquinoxLoggerEngineImplMock : public equinox::IEquinoxLoggerEngineImpl {
       public:
        MOCK_METHOD(void, logMessage, (equinox::level::LOG_LEVEL msgLevel, const std::string& formatedOutputMessage), (override));
        MOCK_METHOD(bool, setup,
                    (equinox::level::LOG_LEVEL logLevel, const std::string& logPrefix, equinox::logs_output::SINK logsOutputSink,
                     const std::string& logFileName, std::size_t maxLogFileSizeBytes, std::size_t maxLogFiles),
                    (override));
        MOCK_METHOD(void, changeLevel, (equinox::level::LOG_LEVEL logLevel), (override));
        MOCK_METHOD(bool, changeLogsOutputSink, (equinox::logs_output::SINK logsOutputSink), (override));
        MOCK_METHOD(void, flush, (), (override));
    };
}  // namespace mocks