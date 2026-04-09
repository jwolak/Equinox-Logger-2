#pragma once

#include <gmock/gmock.h>

#include "IColorFormatter.h"

namespace mocks {
    class ColorFormatterMock : public equinox::IColorFormatter {
       public:
        MOCK_METHOD1(extractLevelFromMessage, equinox::level::LOG_LEVEL(const std::string& message));
        MOCK_METHOD2(applyConsoleColors, std::string(const std::string& message, std::string_view color));
        MOCK_METHOD1(getColorForLevel, std::string_view(equinox::level::LOG_LEVEL logLevel));
    };
}  // namespace mocks