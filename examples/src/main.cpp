/*
 * main.cpp
 *
 * Copylefts (C) 2022
 * Author: Janusz Wolak

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <iostream>

#include "EquinoxLogger.h"

int main(void) {

  equinox::setLevel(equinox::level::LOG_LEVEL::trace);
  equinox::setBacktrace(10);
  equinox::setLogsOutputSink(equinox::logs_output::SINK::console_and_file);

  equinox::trace(   "Example trace log no:    [%d]" , 1);
  equinox::debug(   "Example debug log no:    [%d]" , 2);
  equinox::info(    "Example info log no:     [%d]" , 3);
  equinox::warning( "Example warning log no:  [%d]" , 4);
  equinox::error(   "Example error log no:    [%d]" , 5);
  equinox::critical("Example critical log no: [%d]" , 6);

  LOG_TRACE("Example LOG_TRACE log no:    [%d]" , 1);

	return 0;
}
