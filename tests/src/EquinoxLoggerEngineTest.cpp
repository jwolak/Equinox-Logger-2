#include <gtest/gtest.h>

#include "EquinoxLoggerEngine.h"
#include "EquinoxLoggerEngineImplMock.h"

namespace equinox_logger_engine_impl_test {
    using namespace equinox;
    using namespace mocks;
    using namespace testing;

    namespace {
        const std::string kTestLogFileName = "test.log";
        const std::size_t kTestMaxLogFileSizeBytes = 1024 * 1024;  // 1 MB
        const std::size_t kTestMaxLogFiles = 5;
        const std::string kTestLogPrefix = "TestPrefix";
    }  // namespace

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

    class EquinoxLoggerEngineSetupParamTest : public ::testing::TestWithParam<level::LOG_LEVEL> {
       public:
        EquinoxLoggerEngineSetupParamTest()
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

    TEST_P(EquinoxLoggerEngineSetupParamTest, Call_Setup_With_Various_Levels_Console_Sink_And_Verify_Parameters_And_Returns_True) {
        const auto logLevel = GetParam();

        EXPECT_CALL(*equinox_logger_engine_impl_mock,
                    setup(logLevel, kTestLogPrefix, logs_output::SINK::console, kTestLogFileName, kTestMaxLogFileSizeBytes, kTestMaxLogFiles))
            .Times(1)
            .WillOnce(Return(true));

        EXPECT_TRUE(
            equinox_logger_engine.setup(logLevel, kTestLogPrefix, logs_output::SINK::console, kTestLogFileName, kTestMaxLogFileSizeBytes, kTestMaxLogFiles));
    }

    INSTANTIATE_TEST_SUITE_P(SetupWithAllLogLevels, EquinoxLoggerEngineSetupParamTest,
                             Values(level::LOG_LEVEL::trace, level::LOG_LEVEL::debug, level::LOG_LEVEL::info, level::LOG_LEVEL::warning,
                                    level::LOG_LEVEL::error, level::LOG_LEVEL::critical));

}  // namespace equinox_logger_engine_impl_test