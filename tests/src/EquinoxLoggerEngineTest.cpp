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

    TEST_F(EquinoxLoggerEngineTest, Call_GetInstance_And_Returns_Same_Instance) {
        EquinoxLoggerEngine& instance1 = EquinoxLoggerEngine::getInstance();
        EquinoxLoggerEngine& instance2 = EquinoxLoggerEngine::getInstance();

        EXPECT_EQ(&instance1, &instance2);
    }

    TEST_F(EquinoxLoggerEngineTest, Call_Setup_And_Verify_Parameters) {
        EXPECT_CALL(*equinox_logger_engine_impl_mock, setup(level::LOG_LEVEL::info, "TestPrefix", logs_output::SINK::console, "test.log", 1024 * 1024, 5))
            .Times(1)
            .WillOnce(Return(true));

        bool result = equinox_logger_engine.setup(level::LOG_LEVEL::info, "TestPrefix", logs_output::SINK::console, "test.log", 1024 * 1024, 5);
        EXPECT_TRUE(result);
    }
}  // namespace equinox_logger_engine_impl_test