/*
 * EquinoxLogger-LoggerEngineLogic.cpp
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

#include "EquinoxLogger-LoggerEngineLogic.h"

void equinox::LoggerEngineLogic::setLogLevel(equinox::level::LOG_LEVEL logLevel)
{
  mLogLevel = logLevel;
}

void equinox::LoggerEngineLogic::setBacktrace(size_t numberOfMessages)
{

}

void equinox::LoggerEngineLogic::setLogsOutputSink(equinox::logs_output::SINK logsOutputSink)
{
  mSink = logsOutputSink;
}
