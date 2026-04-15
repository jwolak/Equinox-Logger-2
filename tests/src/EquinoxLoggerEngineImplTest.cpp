#include <gtest/gtest.h>

#include "EquinoxLoggerEngineImpl.h"

namespace equinox_logger_engine_impl_test {

    using namespace testing;
    using namespace equinox;

    class EquinoxLoggerEngineImplTestable : public EquinoxLoggerEngineImpl {
       public:
        EquinoxLoggerEngineImplTestable(std::shared_ptr<ITimestampProducer> mTimestampProducer, std::shared_ptr<IFileLogsProducer> mFileLogsProducer,
                                        std::unique_ptr<IAsyncLogQueueEngine> mAsyncLogQueueEngine)
            : EquinoxLoggerEngineImpl(mTimestampProducer, mFileLogsProducer, std::move(mAsyncLogQueueEngine)) {}
    };

    class EquinoxLoggerEngineImplTest : public Test {
       public:
        EquinoxLoggerEngineImplTest() {}
    };

}  // namespace equinox_logger_engine_impl_test