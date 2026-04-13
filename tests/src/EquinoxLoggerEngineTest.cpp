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

    TEST_F(EquinoxLoggerEngineTest, Call_GetInstance_And_Returns_Same_Instance) {
        EquinoxLoggerEngine& instance1 = EquinoxLoggerEngine::getInstance();
        EquinoxLoggerEngine& instance2 = EquinoxLoggerEngine::getInstance();

        EXPECT_EQ(&instance1, &instance2);
    }

    TEST_F(EquinoxLoggerEngineTest, Call_Setup_With_Trace_Level_Console_Sink_And_Verify_Parameters_And_Returns_True) {
        EXPECT_CALL(*equinox_logger_engine_impl_mock,
                    setup(level::LOG_LEVEL::trace, kTestLogPrefix, logs_output::SINK::console, kTestLogFileName, kTestMaxLogFileSizeBytes, kTestMaxLogFiles))
            .Times(1)
            .WillOnce(Return(true));

        EXPECT_TRUE(equinox_logger_engine.setup(level::LOG_LEVEL::trace, kTestLogPrefix, logs_output::SINK::console, kTestLogFileName, kTestMaxLogFileSizeBytes,
                                                kTestMaxLogFiles));
    }

    TEST_F(EquinoxLoggerEngineTest, Call_Setup_With_Debug_Level_Console_Sink_And_Verify_Parameters_And_Returns_True) {
        EXPECT_CALL(*equinox_logger_engine_impl_mock,
                    setup(level::LOG_LEVEL::debug, kTestLogPrefix, logs_output::SINK::console, kTestLogFileName, kTestMaxLogFileSizeBytes, kTestMaxLogFiles))
            .Times(1)
            .WillOnce(Return(true));

        EXPECT_TRUE(equinox_logger_engine.setup(level::LOG_LEVEL::debug, kTestLogPrefix, logs_output::SINK::console, kTestLogFileName, kTestMaxLogFileSizeBytes,
                                                kTestMaxLogFiles));
    }

    TEST_F(EquinoxLoggerEngineTest, Call_Setup_With_Info_Level_Console_Sink_And_Verify_Parameters_And_Returns_True) {
        EXPECT_CALL(*equinox_logger_engine_impl_mock,
                    setup(level::LOG_LEVEL::info, kTestLogPrefix, logs_output::SINK::console, kTestLogFileName, kTestMaxLogFileSizeBytes, kTestMaxLogFiles))
            .Times(1)
            .WillOnce(Return(true));

        EXPECT_TRUE(equinox_logger_engine.setup(level::LOG_LEVEL::info, kTestLogPrefix, logs_output::SINK::console, kTestLogFileName, kTestMaxLogFileSizeBytes,
                                                kTestMaxLogFiles));
    }

    TEST_F(EquinoxLoggerEngineTest, Call_Setup_With_Warning_Level_Console_Sink_And_Verify_Parameters_And_Returns_True) {
        EXPECT_CALL(*equinox_logger_engine_impl_mock,
                    setup(level::LOG_LEVEL::warning, kTestLogPrefix, logs_output::SINK::console, kTestLogFileName, kTestMaxLogFileSizeBytes, kTestMaxLogFiles))
            .Times(1)
            .WillOnce(Return(true));

        EXPECT_TRUE(equinox_logger_engine.setup(level::LOG_LEVEL::warning, kTestLogPrefix, logs_output::SINK::console, kTestLogFileName,
                                                kTestMaxLogFileSizeBytes, kTestMaxLogFiles));
    }

    TEST_F(EquinoxLoggerEngineTest, Call_Setup_With_Error_Level_Console_Sink_And_Verify_Parameters_And_Returns_True) {
        EXPECT_CALL(*equinox_logger_engine_impl_mock,
                    setup(level::LOG_LEVEL::error, kTestLogPrefix, logs_output::SINK::console, kTestLogFileName, kTestMaxLogFileSizeBytes, kTestMaxLogFiles))
            .Times(1)
            .WillOnce(Return(true));

        EXPECT_TRUE(equinox_logger_engine.setup(level::LOG_LEVEL::error, kTestLogPrefix, logs_output::SINK::console, kTestLogFileName, kTestMaxLogFileSizeBytes,
                                                kTestMaxLogFiles));
    }

    TEST_F(EquinoxLoggerEngineTest, Call_Setup_With_Critical_Level_Console_Sink_And_Verify_Parameters_And_Returns_True) {
        EXPECT_CALL(*equinox_logger_engine_impl_mock,
                    setup(level::LOG_LEVEL::critical, kTestLogPrefix, logs_output::SINK::console, kTestLogFileName, kTestMaxLogFileSizeBytes, kTestMaxLogFiles))
            .Times(1)
            .WillOnce(Return(true));

        EXPECT_TRUE(equinox_logger_engine.setup(level::LOG_LEVEL::critical, kTestLogPrefix, logs_output::SINK::console, kTestLogFileName,
                                                kTestMaxLogFileSizeBytes, kTestMaxLogFiles));
    }

}  // namespace equinox_logger_engine_impl_test