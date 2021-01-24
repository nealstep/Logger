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
- void valuei(const char* tag, int32_t val, logger_levels log_level=log_level_default) - sends an int 32 with a tag at log level
- void valued(const char* tag, double val, logger_levels log_level=log_level_default) - sends a double with a tag at log level
- void value(const char* tag, const char* msg, logger_levels log_level) - sends a msg with a tag at log level
- void value_long(const char* tag, const char* msg, logger_levels log_level=log_level_default) -send an array of uin32 on mlti lines

- void report(const char* tag, uint32_t val, bool hex=true) - reports a value (uint) with a tag
- void reporti(const char* tag, int32_t val) - report an integer uint32
- void reportd(const char* tag, double val) - report a double
- void report(const char* tag, const char* msg) - reports a msg with a tag
- void report_long(const char* tag, const uint32_t msg[], uint16_t x, uint16_t y=0) - report an array of uint32 on multi lines
