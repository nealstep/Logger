# Logger
A Simple Logging library for serial communiction.

Expects caller to provide a function `void send(const char* msg)` that actually does something with the message (i.e. `Serial.println(msg);`)

creates a global single instance class called `lg`

function calls:
- set_level(logger_levels new_level) - sets new logging level see .h
- void error(const char* msg) - sends msg level error
- void warn(const char* msg) - sends msg level warning
- void info(const char* msg) - sends msg level info
- void debug(const char* msg) - send msg level debug
- void value(const char* tag, uint32_t val, bool hex=true, logger_levels log_level) - sends a value (uint) with a tag at log level
- void value(const char* tag, const char* msg, logger_levels log_level) - sends a msg with a tag at log level
- void report(const char* tag, uint32_t val, bool hex=true) - reports a value (uint) with a tag
- void report(const char* tag, const char* msg) - reports a msg with a tag
