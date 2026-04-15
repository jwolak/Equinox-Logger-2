#include <gtest/gtest.h>

#include <string>

#include "AsyncLogQueueEngineMock.h"
#include "EquinoxLoggerEngineImpl.h"
#include "FileLogsProducerMock.h"
#include "TimestampProducerMock.h"

namespace equinox_logger_engine_impl_test {

    using namespace testing;
    using namespace equinox;
    using namespace mocks;

    namespace {
        constexpr const char* kFormattedOutputMessage = "Test log";

        struct LogLevelTestCase {
            level::LOG_LEVEL level;
            const char* expectedMessage;
            bool shouldProcess;
            const char* testName;
        };

        std::string GetTestCaseName(const TestParamInfo<LogLevelTestCase>& info) {
            return info.param.testName;
        }
    }  // namespace

    class EquinoxLoggerEngineImplTestable : public EquinoxLoggerEngineImpl {
       public:
        EquinoxLoggerEngineImplTestable(std::shared_ptr<ITimestampProducer> mTimestampProducer, std::shared_ptr<IFileLogsProducer> mFileLogsProducer,
                                        std::unique_ptr<IAsyncLogQueueEngine> mAsyncLogQueueEngine)
            : EquinoxLoggerEngineImpl(mTimestampProducer, mFileLogsProducer, std::move(mAsyncLogQueueEngine)) {}
    };

    class EquinoxLoggerEngineImplTest : public Test {
       public:
        EquinoxLoggerEngineImplTest()
            : timestamp_producer_mock{new StrictMock<TimestampProducerMock>()},
              file_logs_producer_mock{new StrictMock<FileLogsProducerMock>()},
              async_log_queue_engine_mock{new StrictMock<AsyncLogQueueEngineMock>()},
              equinox_Logger_engine_impl{std::shared_ptr<ITimestampProducer>(timestamp_producer_mock),
                                         std::shared_ptr<IFileLogsProducer>(file_logs_producer_mock),
                                         std::unique_ptr<IAsyncLogQueueEngine>(async_log_queue_engine_mock)} {}

        StrictMock<TimestampProducerMock>* timestamp_producer_mock;
        StrictMock<FileLogsProducerMock>* file_logs_producer_mock;
        StrictMock<AsyncLogQueueEngineMock>* async_log_queue_engine_mock;
        EquinoxLoggerEngineImplTestable equinox_Logger_engine_impl;
    };

    class EquinoxLoggerEngineImplParameterizedTest : public EquinoxLoggerEngineImplTest, public WithParamInterface<LogLevelTestCase> {};

    TEST_P(EquinoxLoggerEngineImplParameterizedTest, Log_Message_For_All_Log_Levels_Is_Processed_According_To_Level) {
        const LogLevelTestCase testCase = GetParam();

        if (testCase.shouldProcess) {
            EXPECT_CALL(*async_log_queue_engine_mock, startWorkerIfNeeded()).Times(1);
            EXPECT_CALL(*async_log_queue_engine_mock, processLogMessage(testCase.expectedMessage)).Times(1);
        } else {
            EXPECT_CALL(*async_log_queue_engine_mock, startWorkerIfNeeded()).Times(0);
            EXPECT_CALL(*async_log_queue_engine_mock, processLogMessage(_)).Times(0);
        }

        equinox_Logger_engine_impl.logMessage(testCase.level, kFormattedOutputMessage);
    }

    INSTANTIATE_TEST_SUITE_P(AllLogLevels, EquinoxLoggerEngineImplParameterizedTest,
                             Values(LogLevelTestCase{level::LOG_LEVEL::trace, "[TRACE] Test log", true, "Trace"},
                                    LogLevelTestCase{level::LOG_LEVEL::debug, "[DEBUG] Test log", true, "Debug"},
                                    LogLevelTestCase{level::LOG_LEVEL::info, "[INFO] Test log", true, "Info"},
                                    LogLevelTestCase{level::LOG_LEVEL::warning, "[WARNING] Test log", true, "Warning"},
                                    LogLevelTestCase{level::LOG_LEVEL::error, "[ERROR] Test log", true, "Error"},
                                    LogLevelTestCase{level::LOG_LEVEL::critical, "[CRITICAL] Test log", true, "Critical"},
                                    LogLevelTestCase{level::LOG_LEVEL::off, "", false, "Off"}),
                             GetTestCaseName);

}  // namespace equinox_logger_engine_impl_test