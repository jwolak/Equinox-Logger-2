#include <gtest/gtest.h>

#include "ColorFormatterMock.h"
#include "ConsoleLogsProducer.h"
#include "TimestampProducerMock.h"

namespace console_logs_producer_test {

    using namespace equinox;
    using namespace testing;
    using namespace mocks;

    class ConsoleLogsProducerTestable : public ConsoleLogsProducer {
       public:
        ConsoleLogsProducerTestable(std::shared_ptr<ITimestampProducer> timestampProducer, std::shared_ptr<IColorFormatter> colorFormatter)
            : ConsoleLogsProducer(timestampProducer, colorFormatter) {}
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

    TEST_F(ConsoleLogsProducerTest, Log_Message_And_It_Is_Properly_Formatted) {
        std::string messageToLog = "Test log message";
        std::string timestamp = "2023-10-01 12:00:00";
        std::string timestampInUs = ".123456";
        std::string coloredMessage = "\033[31mTest log message\033[0m";
        std::string_view color = "\033[31m";
        equinox::level::LOG_LEVEL logLevel = equinox::level::LOG_LEVEL::error;
        std::string expectedOutput = timestamp + timestampInUs + coloredMessage;
        EXPECT_CALL(*timestamp_producer_mock, getTimestamp()).WillOnce(Return(timestamp));
        EXPECT_CALL(*timestamp_producer_mock, getTimestampInUs()).WillOnce(Return(timestampInUs));
        EXPECT_CALL(*color_formatter_mock, extractLevelFromMessage(messageToLog)).WillOnce(Return(logLevel));
        EXPECT_CALL(*color_formatter_mock, getColorForLevel(logLevel)).WillOnce(Return(color));
        EXPECT_CALL(*color_formatter_mock, applyConsoleColors(messageToLog, color)).WillOnce(Return(coloredMessage));

        console_logs_producer.logMessage(messageToLog);
    }

    TEST_F(ConsoleLogsProducerTest, Flush_Cout_And_It_Does_Not_Throw) {
        EXPECT_NO_THROW(console_logs_producer.flush());
    }

}  // namespace console_logs_producer_test