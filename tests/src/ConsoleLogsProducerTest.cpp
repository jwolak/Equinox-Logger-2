#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include "ColorFormatterMock.h"
#include "ConsoleLogsProducer.h"
#include "TimestampProducerMock.h"

namespace console_logs_producer_test {

    namespace {
        struct LogMessageTestCase {
            equinox::level::LOG_LEVEL level;
            std::string_view color;
            std::string formattedMessage;
        };

        constexpr const char* kMessageToLog = "Test log message";
        const std::string kTimestamp = "2023-10-01 12:00:00";
        const std::string kTimestampInUs = ".123456";

        const LogMessageTestCase kErrorCase{equinox::level::LOG_LEVEL::error, "\033[31m", "\033[31mTest log message\033[0m"};
        const LogMessageTestCase kTraceCase{equinox::level::LOG_LEVEL::trace, "\033[36m", "\033[36mTest log message\033[0m"};
        const LogMessageTestCase kDebugCase{equinox::level::LOG_LEVEL::debug, "\033[32m", "\033[32mTest log message\033[0m"};
        const LogMessageTestCase kInfoCase{equinox::level::LOG_LEVEL::info, "", "Test log message"};
        const LogMessageTestCase kWarningCase{equinox::level::LOG_LEVEL::warning, "\033[33m", "\033[33mTest log message\033[0m"};
        const LogMessageTestCase kCriticalCase{equinox::level::LOG_LEVEL::critical, "\033[35m", "\033[35mTest log message\033[0m"};
    }  // namespace

    using namespace equinox;
    using namespace testing;
    using namespace mocks;

    class ConsoleLogsProducerTestable : public ConsoleLogsProducer {
       public:
        ConsoleLogsProducerTestable(std::shared_ptr<ITimestampProducer> timestampProducer, std::shared_ptr<IColorFormatter> colorFormatter)
            : ConsoleLogsProducer(timestampProducer, colorFormatter) {}
    };

    class TrackingStringBuf : public std::stringbuf {
       public:
        int syncCalls = 0;

       protected:
        int sync() override {
            ++syncCalls;
            return std::stringbuf::sync();
        }
    };

    class CoutBufferGuard {
       public:
        explicit CoutBufferGuard(std::streambuf* newBuffer) : oldBuffer_(std::cout.rdbuf(newBuffer)) {}

        ~CoutBufferGuard() {
            std::cout.rdbuf(oldBuffer_);
        }

       private:
        std::streambuf* oldBuffer_;
    };

    class ConsoleLogsProducerTest : public ::testing::Test {
       public:
        ConsoleLogsProducerTest()
            : timestamp_producer_mock{new StrictMock<TimestampProducerMock>},
              color_formatter_mock{new StrictMock<ColorFormatterMock>},
              console_logs_producer{std::shared_ptr<ITimestampProducer>(timestamp_producer_mock), std::shared_ptr<IColorFormatter>(color_formatter_mock)} {}

        StrictMock<TimestampProducerMock>* timestamp_producer_mock;
        StrictMock<ColorFormatterMock>* color_formatter_mock;
        ConsoleLogsProducerTestable console_logs_producer;
    };

    class ConsoleLogsProducerParamTest : public ConsoleLogsProducerTest, public ::testing::WithParamInterface<LogMessageTestCase> {};

    TEST_P(ConsoleLogsProducerParamTest, Log_Message_And_It_Is_Properly_Formatted) {
        const LogMessageTestCase& testCase = GetParam();
        std::string expectedOutput = kTimestamp + kTimestampInUs + testCase.formattedMessage;

        EXPECT_CALL(*timestamp_producer_mock, getTimestamp()).WillOnce(Return(kTimestamp));
        EXPECT_CALL(*timestamp_producer_mock, getTimestampInUs()).WillOnce(Return(kTimestampInUs));
        EXPECT_CALL(*color_formatter_mock, extractLevelFromMessage(kMessageToLog)).WillOnce(Return(testCase.level));
        EXPECT_CALL(*color_formatter_mock, getColorForLevel(testCase.level)).WillOnce(Return(testCase.color));
        EXPECT_CALL(*color_formatter_mock, applyConsoleColors(kMessageToLog, testCase.color)).WillOnce(Return(testCase.formattedMessage));

        testing::internal::CaptureStdout();
        console_logs_producer.logMessage(kMessageToLog);
        std::string output = testing::internal::GetCapturedStdout();

        EXPECT_EQ(output, expectedOutput + "\n");
    }

    INSTANTIATE_TEST_SUITE_P(AllLogLevels, ConsoleLogsProducerParamTest, Values(kErrorCase, kTraceCase, kDebugCase, kInfoCase, kWarningCase, kCriticalCase));

    TEST_F(ConsoleLogsProducerTest, Flush_Cout_And_It_Synchronizes_Stream_Buffer) {
        TrackingStringBuf trackingBuffer;
        CoutBufferGuard coutGuard(&trackingBuffer);

        console_logs_producer.flush();

        EXPECT_GT(trackingBuffer.syncCalls, 0);
    }

}  // namespace console_logs_producer_test