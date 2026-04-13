#include <gtest/gtest.h>

#include <algorithm>

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

    class EquinoxLoggerEngineSinkParamTest : public ::testing::TestWithParam<logs_output::SINK> {
       public:
        EquinoxLoggerEngineSinkParamTest()
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

    TEST_F(EquinoxLoggerEngineTest, Call_Log_With_Format_Arguments_And_Verify_LogMessage_Called_With_Formatted_Text) {
        EXPECT_CALL(*equinox_logger_engine_impl_mock, logMessage(level::LOG_LEVEL::info, "Test value: 42")).Times(1);

        equinox_logger_engine.log(level::LOG_LEVEL::info, "Test %s: %d", "value", 42);
    }

    TEST_F(EquinoxLoggerEngineTest, Call_Log_With_Message_Exceeding_Buffer_Size_And_Verify_Message_Is_Truncated_And_LogMessage_Is_Called) {
        const std::string veryLongMessage(5000, 'A');

        EXPECT_CALL(*equinox_logger_engine_impl_mock, logMessage(level::LOG_LEVEL::warning, Truly([](const std::string& msg) {
                                                                     return msg.size() == 4095 &&
                                                                         std::all_of(msg.begin(), msg.end(), [](char c) { return c == 'A'; });
                                                                 })))
            .Times(1);

        equinox_logger_engine.log(level::LOG_LEVEL::warning, "%s", veryLongMessage.c_str());
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

    TEST_P(EquinoxLoggerEngineSetupParamTest, Try_Setup_But_EquinoxLoggerEngineImpl_Returns_False_And_False_Is_Returned) {
        const auto logLevel = GetParam();
        EXPECT_CALL(*equinox_logger_engine_impl_mock,
                    setup(logLevel, kTestLogPrefix, logs_output::SINK::console, kTestLogFileName, kTestMaxLogFileSizeBytes, kTestMaxLogFiles))
            .Times(1)
            .WillOnce(Return(false));

        EXPECT_FALSE(
            equinox_logger_engine.setup(logLevel, kTestLogPrefix, logs_output::SINK::console, kTestLogFileName, kTestMaxLogFileSizeBytes, kTestMaxLogFiles));
    }

    TEST_P(EquinoxLoggerEngineSetupParamTest, Change_Level_And_Verify_ChangeLevel_Called_With_Correct_Parameter) {
        const auto logLevel = GetParam();
        EXPECT_CALL(*equinox_logger_engine_impl_mock, changeLevel(logLevel)).Times(1);

        equinox_logger_engine.changeLevel(logLevel);
    }

    TEST_P(EquinoxLoggerEngineSinkParamTest, Change_Logs_Output_Sink_And_Verify_ChangeLogsOutputSink_Called_With_Correct_Parameter_And_Returns_True) {
        const auto sink = GetParam();
        EXPECT_CALL(*equinox_logger_engine_impl_mock, changeLogsOutputSink(sink)).Times(1).WillOnce(Return(true));
        EXPECT_TRUE(equinox_logger_engine.changeLogsOutputSink(sink));
    }

    INSTANTIATE_TEST_SUITE_P(ChangeLogsOutputSinkWithAllSupportedSinks, EquinoxLoggerEngineSinkParamTest,
                             Values(logs_output::SINK::console, logs_output::SINK::file, logs_output::SINK::console_and_file));

    TEST_F(EquinoxLoggerEngineTest, Call_Flush_And_Verify_Flush_Called) {
        EXPECT_CALL(*equinox_logger_engine_impl_mock, flush()).Times(1);

        equinox_logger_engine.flush();
    }

}  // namespace equinox_logger_engine_impl_test