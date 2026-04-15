#include <gtest/gtest.h>

#include "AsyncLogQueueEngineMock.h"
#include "EquinoxLoggerEngineImpl.h"
#include "FileLogsProducerMock.h"
#include "TimestampProducerMock.h"

namespace equinox_logger_engine_impl_test {

    using namespace testing;
    using namespace equinox;
    using namespace mocks;

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

}  // namespace equinox_logger_engine_impl_test