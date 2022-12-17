/*
 * Equinox-Logger-LoggerManager.cpp
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

#include "EquinoxLogger-LoggerManager.h"

equinox::LoggerEngine* equinox::LoggerManager::mLoggerEngineInstance_ { nullptr };
std::mutex equinox::LoggerManager::mLoggerEngineInstanceMutex_;

EQUINOX_INLINE equinox::LoggerEngine* equinox::LoggerManager::GetLoggerEngineInstance()
{
    std::lock_guard<std::mutex> lock(equinox::LoggerManager::mLoggerEngineInstanceMutex_);

    if (equinox::LoggerManager::mLoggerEngineInstance_  == nullptr) {
        equinox::LoggerManager::mLoggerEngineInstance_  = new equinox::LoggerEngine();
    }

    return equinox::LoggerManager::mLoggerEngineInstance_;
}
