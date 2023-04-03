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
- configured build to shared/static lib

## Building for source
```sh
cmake CMakeLists.txt
make
```
## Install
```sh
$ sudo make install (Ubuntu)
or
# make install
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

**Output:**

./EquinoxLoggerExamples 
[Mon Apr  3 15:43:39 2023][1680529419785][equinox-test][TRACE] Example trace log no:    [1]
[Mon Apr  3 15:43:39 2023][1680529419787][equinox-test][DEBUG] Example debug log no:    [2]
[Mon Apr  3 15:43:39 2023][1680529419787][equinox-test][INFO] Example info log no:     [3]
[Mon Apr  3 15:43:39 2023][1680529419788][equinox-test][WARNING] Example warning log no:  [4]
[Mon Apr  3 15:43:39 2023][1680529419788][equinox-test][ERROR] Example error log no:    [5]
[Mon Apr  3 15:43:39 2023][1680529419788][equinox-test][CRITICAL] Example critical log no: [6]

```
## License

**BSD 3-Clause License**
<br/>Copyright (c) 2023, Janusz Wolak
<br/>All rights reserved.
