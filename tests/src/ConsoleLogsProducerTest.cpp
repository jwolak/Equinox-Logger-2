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
}  // namespace console_logs_producer_test