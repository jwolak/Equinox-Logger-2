#include <gtest/gtest.h>

#include <memory>

#include "FileLogsProducer.h"
#include "TimestampProducerMock.h"

namespace file_logs_producer_test {
    using namespace equinox;
    using namespace testing;
    using namespace mocks;

    class FileLogsProducerTest : public Test {
    public:
        FileLogsProducerTest() : timestamp_producer_mock(std::make_shared<StrictMock<TimestampProducerMock>>()), file_logs_producer(timestamp_producer_mock) {}
        
        std::shared_ptr<StrictMock<TimestampProducerMock>> timestamp_producer_mock;
        FileLogsProducer file_logs_producer;
    };

}