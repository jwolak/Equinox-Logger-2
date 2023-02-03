/*
 * EquinoxLogger-LoggerEngine.cpp
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

#include "EquinoxLogger-LoggerEngine.h"

void equinox::LoggerEngine::setup(equinox::level::LOG_LEVEL logLevel, std::string logPrefix, equinox::logs_output::SINK logsOutputSink, std::string logFileName)
{
  mLogLevel_ = logLevel;
  mLogPrefix_ = std::string("[" + logPrefix + "]");
  mLogsProducer_->setLogsOutputSink(logsOutputSink);

  if(equinox::logs_output::SINK::file == logsOutputSink or equinox::logs_output::SINK::console_and_file == logsOutputSink)
  {
    mFileLogsProducer_->setupFile(logFileName);
  }

}

void equinox::LoggerEngine::setLogLevel(level::LOG_LEVEL logLevel)
{
  mLogLevel_ = logLevel;
}

void equinox::LoggerEngine::setLogsOutputSink(logs_output::SINK logsOutputSink)
{
  mLogsProducer_->setLogsOutputSink(logsOutputSink);
}
