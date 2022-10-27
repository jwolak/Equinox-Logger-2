/*
 * Common.h
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

#ifndef INCLUDE_EQUINOXLOGGER_COMMON_H_
#define INCLUDE_EQUINOXLOGGER_COMMON_H_

#if defined(EQUINOX_SHARED_SHARED_LIB)
#            define EQUINOX_API __attribute__((visibility("default")))
#else // !defined(EQUINOX_SHARED_SHARED_LIB)
#    define EQUINOX_API
#    define EQUINOX_HEADER_ONLY
#    define EQUINOX_INLINE inline
#endif // #ifdef EQUINOX_SHARED_SHARED_LIB

#endif /* INCLUDE_EQUINOXLOGGER_COMMON_H_ */
