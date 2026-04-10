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

        std::string ReadFileContents(const std::string& filePath) {
            std::ifstream file(filePath);
            if (!file.is_open()) {
                return "";
            }

            return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
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

    TEST(EquinoxLoggerApiTest, Setup_With_Console_Sink_And_Returns_True) {
        ASSERT_TRUE(equinox::setup(equinox::level::LOG_LEVEL::trace, "EquinoxLoggerApiTest", equinox::logs_output::SINK::console));
    }

    TEST(EquinoxLoggerApiTest, Setup_With_Console_And_File_Sink_And_Returns_True) {
        ASSERT_TRUE(equinox::setup(equinox::level::LOG_LEVEL::trace, "EquinoxLoggerApiTest", equinox::logs_output::SINK::console_and_file,
                                   "/tmp/equinox_logger_api_test.log"));
    }

    TEST(EquinoxLoggerApiTest, Setup_With_File_Sink_And_Returns_True) {
        ASSERT_TRUE(equinox::setup(equinox::level::LOG_LEVEL::trace, "EquinoxLoggerApiTest", equinox::logs_output::SINK::file));
    }

    TEST(EquinoxLoggerApiTest, Setup_With_Invalid_File_Path_Returns_False) {
        ASSERT_FALSE(equinox::setup(equinox::level::LOG_LEVEL::trace, "EquinoxLoggerApiTest", equinox::logs_output::SINK::file,
                                    "/invalid_path_for_equinox_logger/does_not_exist/test.log"));
    }

    TEST(EquinoxLoggerApiTest, Change_Level_Then_Logger_Proceeds_With_Current_Level) {
        const std::string logFilePath = "/tmp/equinox_logger_change_level_test.log";
        std::filesystem::remove(logFilePath);

        ASSERT_TRUE(equinox::setup(equinox::level::LOG_LEVEL::trace, "EquinoxLoggerApiTest", equinox::logs_output::SINK::file, logFilePath));
        equinox::flush();

        equinox::changeLevel(equinox::level::LOG_LEVEL::error);

        equinox::info("%s", "message_that_should_be_filtered");
        equinox::error("%s", "message_that_should_be_printed");
        equinox::flush();

        EXPECT_TRUE(WaitForFileToContain(logFilePath, "message_that_should_be_printed"));
        const std::string output = ReadFileContents(logFilePath);

        EXPECT_EQ(output.find("message_that_should_be_filtered"), std::string::npos);
        EXPECT_NE(output.find("message_that_should_be_printed"), std::string::npos);
    }

    TEST(EquinoxLoggerApiTest, Flush_Does_Not_Crash_When_Called_After_Setup) {
        ASSERT_TRUE(equinox::setup(equinox::level::LOG_LEVEL::trace, "EquinoxLoggerApiTest", equinox::logs_output::SINK::console));

        EXPECT_NO_FATAL_FAILURE(equinox::flush());
    }

    TEST(EquinoxLoggerApiTest, Trace_Emits_Expected_Level_And_Message) {
        VerifyLogEmission("[TRACE]", "trace_public_api_message", []() { equinox::trace("%s", "trace_public_api_message"); });
    }

    TEST(EquinoxLoggerApiTest, Debug_Emits_Expected_Level_And_Message) {
        VerifyLogEmission("[DEBUG]", "debug_public_api_message", []() { equinox::debug("%s", "debug_public_api_message"); });
    }

    TEST(EquinoxLoggerApiTest, Info_Emits_Expected_Level_And_Message) {
        VerifyLogEmission("[INFO]", "info_public_api_message", []() { equinox::info("%s", "info_public_api_message"); });
    }

    TEST(EquinoxLoggerApiTest, Warning_Emits_Expected_Level_And_Message) {
        VerifyLogEmission("[WARNING]", "warning_public_api_message", []() { equinox::warning("%s", "warning_public_api_message"); });
    }

    TEST(EquinoxLoggerApiTest, Error_Emits_Expected_Level_And_Message) {
        VerifyLogEmission("[ERROR]", "error_public_api_message", []() { equinox::error("%s", "error_public_api_message"); });
    }

    TEST(EquinoxLoggerApiTest, Critical_Emits_Expected_Level_And_Message) {
        VerifyLogEmission("[CRITICAL]", "critical_public_api_message", []() { equinox::critical("%s", "critical_public_api_message"); });
    }

}  // namespace equinox_logger_api_test
