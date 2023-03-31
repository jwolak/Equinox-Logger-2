# Equinox logging engine 2.1
**Thread safety C++ logger version 2.1**

**Logger with support logging to file, console or both. Six levels available:**
- Trace 
- Debug
- Info
- Warning
- Error
- Critical
- Off

## Features

- settable log level
- settable output direction (console, file or both)
- powered by C++11/14
- configured build to shared/static lib

## Building for source
```sh
cmake CMakeLists.txt
make
```
## Example:

Include "EquinoxLogger.h" to your source code:
```sh
See: examples/src/EquinoxLoggerExamples.cpp
```
```sh
#include "EquinoxLogger.h"

int main(void) {

  equinox::setup(equinox::level::LOG_LEVEL::trace, std::string("equinox-test"), equinox::logs_output::SINK::console_and_file, std::string("equinox.log"));

  equinox::trace(   "Example trace log no:    [%d]" , 1);
  equinox::debug(   "Example debug log no:    [%d]" , 2);
  equinox::info(    "Example info log no:     [%d]" , 3);
  equinox::warning( "Example warning log no:  [%d]" , 4);
  equinox::error(   "Example error log no:    [%d]" , 5);
  equinox::critical("Example critical log no: [%d]" , 6);

  return 0;
}
```
## License

BSD 3-Clause License<br\>
***EquinoxLogger 2.0 Copyright (c) 2023, Janusz Wolak***
*Glory for Free Software!*
