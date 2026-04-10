#include <chrono>

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <functional>
#include <string>
#include <thread>

#include "EquinoxLogger.h"

namespace equinox_logger_api_test {

    namespace {

        bool WaitForFileToContain(const std::string& filePath, const std::string& expectedToken) {
            for (int attempt = 0; attempt < 40; ++attempt) {
                std::ifstream file(filePath);
                if (file.is_open()) {
                    const std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                    if (content.find(expectedToken) != std::string::npos) {
                        return true;
                    }
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }

            return false;
        }

        void VerifyLogEmission(const std::string& levelTag, const std::string& message, const std::function<void()>& logFn) {
            const std::string logFilePath = "/tmp/equinox_logger_api_" + message + ".log";
            std::filesystem::remove(logFilePath);

            ASSERT_TRUE(equinox::setup(equinox::level::LOG_LEVEL::trace, "EquinoxLoggerApiTest", equinox::logs_output::SINK::file, logFilePath));
            equinox::flush();

            logFn();
            equinox::flush();

            EXPECT_TRUE(WaitForFileToContain(logFilePath, levelTag));
            EXPECT_TRUE(WaitForFileToContain(logFilePath, message));
        }

    }  // namespace

    TEST(EquinoxLoggerApiTest, Setup_WithConsoleSink_ReturnsTrue) {
        const bool setupResult = equinox::setup(equinox::level::LOG_LEVEL::trace, "EquinoxLoggerApiTest", equinox::logs_output::SINK::console);

        EXPECT_TRUE(setupResult);
    }

    TEST(EquinoxLoggerApiTest, Setup_WithInvalidFilePath_ReturnsFalse) {
        const bool setupResult = equinox::setup(equinox::level::LOG_LEVEL::trace, "EquinoxLoggerApiTest", equinox::logs_output::SINK::file,
                                                "/invalid_path_for_equinox_logger/does_not_exist/test.log");

        EXPECT_FALSE(setupResult);
    }

    TEST(EquinoxLoggerApiTest, ChangeLogsOutputSink_ToConsole_ReturnsTrue) {
        ASSERT_TRUE(equinox::setup(equinox::level::LOG_LEVEL::trace, "EquinoxLoggerApiTest", equinox::logs_output::SINK::console));

        const bool changeResult = equinox::changeLogsOutputSink(equinox::logs_output::SINK::console);

        EXPECT_TRUE(changeResult);
    }

    TEST(EquinoxLoggerApiTest, ChangeLevel_Then_Log_Respects_CurrentLevel) {
        ASSERT_TRUE(equinox::setup(equinox::level::LOG_LEVEL::trace, "EquinoxLoggerApiTest", equinox::logs_output::SINK::console));
        equinox::flush();

        equinox::changeLevel(equinox::level::LOG_LEVEL::error);

        testing::internal::CaptureStdout();
        equinox::info("%s", "message_that_should_be_filtered");
        equinox::error("%s", "message_that_should_be_printed");
        equinox::flush();
        const std::string output = testing::internal::GetCapturedStdout();

        EXPECT_EQ(output.find("message_that_should_be_filtered"), std::string::npos);
        EXPECT_NE(output.find("message_that_should_be_printed"), std::string::npos);
    }

    TEST(EquinoxLoggerApiTest, Flush_DoesNotCrash_WhenCalledAfterSetup) {
        ASSERT_TRUE(equinox::setup(equinox::level::LOG_LEVEL::trace, "EquinoxLoggerApiTest", equinox::logs_output::SINK::console));

        EXPECT_NO_FATAL_FAILURE(equinox::flush());
    }

    TEST(EquinoxLoggerApiTest, Trace_EmitsExpectedLevelAndMessage) {
        VerifyLogEmission("[TRACE]", "trace_public_api_message", []() { equinox::trace("%s", "trace_public_api_message"); });
    }

    TEST(EquinoxLoggerApiTest, Debug_EmitsExpectedLevelAndMessage) {
        VerifyLogEmission("[DEBUG]", "debug_public_api_message", []() { equinox::debug("%s", "debug_public_api_message"); });
    }

    TEST(EquinoxLoggerApiTest, Info_EmitsExpectedLevelAndMessage) {
        VerifyLogEmission("[INFO]", "info_public_api_message", []() { equinox::info("%s", "info_public_api_message"); });
    }

    TEST(EquinoxLoggerApiTest, Warning_EmitsExpectedLevelAndMessage) {
        VerifyLogEmission("[WARNING]", "warning_public_api_message", []() { equinox::warning("%s", "warning_public_api_message"); });
    }

    TEST(EquinoxLoggerApiTest, Error_EmitsExpectedLevelAndMessage) {
        VerifyLogEmission("[ERROR]", "error_public_api_message", []() { equinox::error("%s", "error_public_api_message"); });
    }

    TEST(EquinoxLoggerApiTest, Critical_EmitsExpectedLevelAndMessage) {
        VerifyLogEmission("[CRITICAL]", "critical_public_api_message", []() { equinox::critical("%s", "critical_public_api_message"); });
    }

}  // namespace equinox_logger_api_test
