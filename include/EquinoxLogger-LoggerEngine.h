/*
 * EquinoxLogger-LoggerEngine.h
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
#ifndef INCLUDE_EQUINOXLOGGER_LOGGERENGINE_H_
#define INCLUDE_EQUINOXLOGGER_LOGGERENGINE_H_

#include "EquinoxLogger-Common.h"
#include "EquinoxLogger-LoggerEngineLogic.h"

#include <memory>

namespace equinox {

class EQUINOX_API LoggerEngine
{
     public:
        LoggerEngine()
        : mLoggerEngineLogic_ { std::make_shared<LoggerEngineLogic>() }
        {
        }

        bool setLogLevel(level::LOG_LEVEL logLevel);

     private:
        std::shared_ptr<LoggerEngineLogic> mLoggerEngineLogic_;

};

} /*namespace equinox*/

#endif /* INCLUDE_EQUINOXLOGGER_LOGGERENGINE_H_ */
