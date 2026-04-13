#include <gtest/gtest.h>

#include "EquinoxLoggerEngine.h"
#include "EquinoxLoggerEngineImplMock.h"

namespace equinox_logger_engine_impl_test {
    using namespace equinox;
    using namespace mocks;
    using namespace testing;

    class EquinoxLoggerEngineTestable : public EquinoxLoggerEngine {
       public:
        EquinoxLoggerEngineTestable(std::unique_ptr<IEquinoxLoggerEngineImpl> mEquinoxLoggerEngineImpl)
            : EquinoxLoggerEngine(std::move(mEquinoxLoggerEngineImpl)) {}
    };

    class EquinoxLoggerEngineTest : public ::testing::Test {
       public:
        EquinoxLoggerEngineTest()
            : equinox_logger_engine_impl_mock{new StrictMock<EquinoxLoggerEngineImplMock>()},
              equinox_logger_engine{std::unique_ptr<IEquinoxLoggerEngineImpl>(equinox_logger_engine_impl_mock)} {}

        StrictMock<EquinoxLoggerEngineImplMock>* equinox_logger_engine_impl_mock;
        EquinoxLoggerEngineTestable equinox_logger_engine;
    };
}  // namespace equinox_logger_engine_impl_test