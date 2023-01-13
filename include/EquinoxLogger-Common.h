/*
 * EquinoxLogger-Common.h
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
#            undef EQUINOX_HEADER_ONLY
#            define EQUINOX_API __attribute__((visibility("default")))
#            define EQUINOX_INLINE
#else // !defined(EQUINOX_SHARED_SHARED_LIB)
#    define EQUINOX_API
#    define EQUINOX_HEADER_ONLY
#    define EQUINOX_INLINE inline
#endif // #ifdef EQUINOX_SHARED_SHARED_LIB

#define EQUINOX_LEVEL_TRACE     0
#define EQUINOX_LEVEL_DEBUG     1
#define EQUINOX_LEVEL_INFO      2
#define EQUINOX_LEVEL_WARNING   3
#define EQUINOX_LEVEL_ERROR     4
#define EQUINOX_LEVEL_CRITICAL  5
#define EQUINOX_LEVEL_OFF       6

#define EQUINOX_SINK_CONSOLE            0
#define EQUINOX_SINK_FILE               1
#define EQUINOX_SINK_CONSOLE_AND_FILE   2

namespace equinox
{
namespace level
{
enum class LOG_LEVEL : int
{
    trace    = EQUINOX_LEVEL_TRACE,
    debug    = EQUINOX_LEVEL_DEBUG,
    info     = EQUINOX_LEVEL_INFO,
    warning  = EQUINOX_LEVEL_WARNING,
    error    = EQUINOX_LEVEL_ERROR,
    critical = EQUINOX_LEVEL_CRITICAL,
    off      = EQUINOX_LEVEL_OFF
};
} /*namespace level*/

namespace logs_output
{
enum class SINK : int
{
    console          = EQUINOX_SINK_CONSOLE,
    file             = EQUINOX_SINK_FILE,
    console_and_file = EQUINOX_SINK_CONSOLE_AND_FILE
};
} /*namespace logs_output*/

} /*namespace equinox*/

#endif /* INCLUDE_EQUINOXLOGGER_COMMON_H_ */
