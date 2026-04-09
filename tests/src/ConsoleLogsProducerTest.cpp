#include <gtest/gtest.h>

#include "ColorFormatterMock.h"
#include "ConsoleLogsProducer.h"
#include "TimestampProducerMock.h"

namespace console_logs_producer_test {

    using namespace equinox;
    using namespace testing;
    using namespace mocks;

    class ConsoleLogsProducerTest : public ::testing::Test {
       public:
        ConsoleLogsProducerTest() {}

        StrictMock<TimestampProducerMock>* timestamp_producer_mock;
        StrictMock<ColorFormatterMock>* color_formatter_mock;
    };
}  // namespace console_logs_producer_test