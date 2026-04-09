#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include "ColorFormatterMock.h"
#include "ConsoleLogsProducer.h"
#include "TimestampProducerMock.h"

namespace console_logs_producer_test {

    namespace {
        constexpr const char* kMessageToLog = "Test log message";
        const std::string kTimestamp = "2023-10-01 12:00:00";
        const std::string kTimestampInUs = ".123456";
        const std::string kColoredMessage = "\033[31mTest log message\033[0m";
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

    TEST_F(ConsoleLogsProducerTest, Log_Message_And_It_Is_Properly_Formatted_For_Error_Level) {
        equinox::level::LOG_LEVEL logLevel = equinox::level::LOG_LEVEL::error;
        std::string expectedOutput = kTimestamp + kTimestampInUs + kColoredMessage;
        std::string_view color = "\033[31m";
        EXPECT_CALL(*timestamp_producer_mock, getTimestamp()).WillOnce(Return(kTimestamp));
        EXPECT_CALL(*timestamp_producer_mock, getTimestampInUs()).WillOnce(Return(kTimestampInUs));
        EXPECT_CALL(*color_formatter_mock, extractLevelFromMessage(kMessageToLog)).WillOnce(Return(logLevel));
        EXPECT_CALL(*color_formatter_mock, getColorForLevel(logLevel)).WillOnce(Return(color));
        EXPECT_CALL(*color_formatter_mock, applyConsoleColors(kMessageToLog, color)).WillOnce(Return(kColoredMessage));

        testing::internal::CaptureStdout();
        console_logs_producer.logMessage(kMessageToLog);
        std::string output = testing::internal::GetCapturedStdout();

        EXPECT_EQ(output, expectedOutput + "\n");
    }

    TEST_F(ConsoleLogsProducerTest, Log_Message_And_It_Is_Properly_Formatted_For_Trace_Level) {
        equinox::level::LOG_LEVEL logLevel = equinox::level::LOG_LEVEL::trace;
        std::string traceColoredMessage = "\033[36mTest log message\033[0m";
        std::string expectedOutput = kTimestamp + kTimestampInUs + traceColoredMessage;
        std::string_view color = "\033[36m";
        EXPECT_CALL(*timestamp_producer_mock, getTimestamp()).WillOnce(Return(kTimestamp));
        EXPECT_CALL(*timestamp_producer_mock, getTimestampInUs()).WillOnce(Return(kTimestampInUs));
        EXPECT_CALL(*color_formatter_mock, extractLevelFromMessage(kMessageToLog)).WillOnce(Return(logLevel));
        EXPECT_CALL(*color_formatter_mock, getColorForLevel(logLevel)).WillOnce(Return(color));
        EXPECT_CALL(*color_formatter_mock, applyConsoleColors(kMessageToLog, color)).WillOnce(Return(traceColoredMessage));

        testing::internal::CaptureStdout();
        console_logs_producer.logMessage(kMessageToLog);
        std::string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, expectedOutput + "\n");
    }

    TEST_F(ConsoleLogsProducerTest, Log_Message_And_It_Is_Properly_Formatted_For_Debug_Level) {
        equinox::level::LOG_LEVEL logLevel = equinox::level::LOG_LEVEL::debug;
        std::string expectedOutput = kTimestamp + kTimestampInUs + kColoredMessage;
        std::string_view color = "\033[32m";
        EXPECT_CALL(*timestamp_producer_mock, getTimestamp()).WillOnce(Return(kTimestamp));
        EXPECT_CALL(*timestamp_producer_mock, getTimestampInUs()).WillOnce(Return(kTimestampInUs));
        EXPECT_CALL(*color_formatter_mock, extractLevelFromMessage(kMessageToLog)).WillOnce(Return(logLevel));
        EXPECT_CALL(*color_formatter_mock, getColorForLevel(logLevel)).WillOnce(Return(color));
        EXPECT_CALL(*color_formatter_mock, applyConsoleColors(kMessageToLog, color)).WillOnce(Return(kColoredMessage));

        testing::internal::CaptureStdout();
        console_logs_producer.logMessage(kMessageToLog);
        std::string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, expectedOutput + "\n");
    }

    TEST_F(ConsoleLogsProducerTest, Log_Message_And_It_Is_Properly_Formatted_For_Info_Level) {
        std::string coloredMessage = "Test log message";
        std::string_view color = "";
        equinox::level::LOG_LEVEL logLevel = equinox::level::LOG_LEVEL::info;
        std::string expectedOutput = kTimestamp + kTimestampInUs + coloredMessage;
        EXPECT_CALL(*timestamp_producer_mock, getTimestamp()).WillOnce(Return(kTimestamp));
        EXPECT_CALL(*timestamp_producer_mock, getTimestampInUs()).WillOnce(Return(kTimestampInUs));
        EXPECT_CALL(*color_formatter_mock, extractLevelFromMessage(kMessageToLog)).WillOnce(Return(logLevel));
        EXPECT_CALL(*color_formatter_mock, getColorForLevel(logLevel)).WillOnce(Return(color));
        EXPECT_CALL(*color_formatter_mock, applyConsoleColors(kMessageToLog, color)).WillOnce(Return(coloredMessage));

        testing::internal::CaptureStdout();
        console_logs_producer.logMessage(kMessageToLog);
        std::string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, expectedOutput + "\n");
    }

    TEST_F(ConsoleLogsProducerTest, Log_Message_And_It_Is_Properly_Formatted_For_Warning_Level) {
        std::string_view color = "\033[33m";
        equinox::level::LOG_LEVEL logLevel = equinox::level::LOG_LEVEL::warning;
        std::string expectedOutput = kTimestamp + kTimestampInUs + kColoredMessage;
        EXPECT_CALL(*timestamp_producer_mock, getTimestamp()).WillOnce(Return(kTimestamp));
        EXPECT_CALL(*timestamp_producer_mock, getTimestampInUs()).WillOnce(Return(kTimestampInUs));
        EXPECT_CALL(*color_formatter_mock, extractLevelFromMessage(kMessageToLog)).WillOnce(Return(logLevel));
        EXPECT_CALL(*color_formatter_mock, getColorForLevel(logLevel)).WillOnce(Return(color));
        EXPECT_CALL(*color_formatter_mock, applyConsoleColors(kMessageToLog, color)).WillOnce(Return(kColoredMessage));

        testing::internal::CaptureStdout();
        console_logs_producer.logMessage(kMessageToLog);
        std::string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, expectedOutput + "\n");
    }

    TEST_F(ConsoleLogsProducerTest, Log_Message_And_It_Is_Properly_Formatted_For_Critical_Level) {
        std::string_view color = "\033[35m";
        equinox::level::LOG_LEVEL logLevel = equinox::level::LOG_LEVEL::critical;
        std::string expectedOutput = kTimestamp + kTimestampInUs + kColoredMessage;
        EXPECT_CALL(*timestamp_producer_mock, getTimestamp()).WillOnce(Return(kTimestamp));
        EXPECT_CALL(*timestamp_producer_mock, getTimestampInUs()).WillOnce(Return(kTimestampInUs));
        EXPECT_CALL(*color_formatter_mock, extractLevelFromMessage(kMessageToLog)).WillOnce(Return(logLevel));
        EXPECT_CALL(*color_formatter_mock, getColorForLevel(logLevel)).WillOnce(Return(color));
        EXPECT_CALL(*color_formatter_mock, applyConsoleColors(kMessageToLog, color)).WillOnce(Return(kColoredMessage));

        testing::internal::CaptureStdout();
        console_logs_producer.logMessage(kMessageToLog);
        std::string output = testing::internal::GetCapturedStdout();
        EXPECT_EQ(output, expectedOutput + "\n");
    }

    TEST_F(ConsoleLogsProducerTest, Flush_Cout_And_It_Synchronizes_Stream_Buffer) {
        TrackingStringBuf trackingBuffer;
        CoutBufferGuard coutGuard(&trackingBuffer);

        console_logs_producer.flush();

        EXPECT_GT(trackingBuffer.syncCalls, 0);
    }

}  // namespace console_logs_producer_test