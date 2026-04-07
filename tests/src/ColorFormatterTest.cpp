/*
 *
 *  Created on: 2026
 *      Author: Janusz Wolak
 */

/*-
 * BSD 3-Clause License
 *
 * Copyright (c) 2026, Janusz Wolak
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

 #include <gtest/gtest.h>

#include <thread>

#include "ColorFormatter.h"

namespace async_log_queue_test {

    using namespace equinox;
    using namespace ::testing;

    class ColorFormatterTest : public ::testing::Test {
        public:
            ColorFormatterTest() : color_formatter{} {}

        ColorFormatter color_formatter;
    };

    TEST_F(ColorFormatterTest, Try_Get_Color_For_Invalid_Level_And_Default_Color_Returned) {
    }

    
    TEST_F(ColorFormatterTest, Get_Color_For_Trace_Level_And_Trace_Color_Returned) {
    }

    TEST_F(ColorFormatterTest, Get_Color_For_Debug_Level_And_Debug_Color_Returned) {
    }

    TEST_F(ColorFormatterTest, Get_Color_For_Info_Level_And_Info_Color_Returned) {
    }

    TEST_F(ColorFormatterTest, Get_Color_For_Warning_Level_And_Warning_Color_Returned) {
    }

    TEST_F(ColorFormatterTest, Get_Color_For_Error_Level_And_Error_Color_Returned) {
    }

    TEST_F(ColorFormatterTest, Get_Color_For_Critical_Level_And_Critical_Color_Returned) {
    }

    TEST_F(ColorFormatterTest, Try_Get_Color_For_Off_Level_And_Default_Color_Returned) {
    }
}