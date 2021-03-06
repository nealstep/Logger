#ifndef LOGGER_H
#define LOGGER_H

#define LOGGER_MSG_LEN 128
#define LOGGER_NUM_LEN 32

#include <Arduino.h>

void send(const char* msg);

enum logger_levels {
    logger_print,
    logger_error,
    logger_warn,
    logger_info,
    logger_debug,
};

static const logger_levels log_level_default=logger_info;

class Logger {
    public:
        static Logger& get_instance() {
            static Logger instance;
            return instance;
        }   
        Logger(Logger const&) = delete;
        void operator=(Logger const&) = delete;

        void set_level(logger_levels new_level);
        void error(const char* msg);
        void warn(const char* msg);
        void info(const char* msg);
        void debug(const char* msg);
        void print(const char* msg);
        void value(const char* tag, uint64_t val, logger_levels log_level=log_level_default, bool hex=true);
        void valuei(const char* tag, int32_t val, logger_levels log_level=log_level_default);
        void valued(const char* tag, double val, logger_levels log_level=log_level_default);
        void value(const char* tag, const char* msg, logger_levels log_level=log_level_default);
        void value_long(const char* tag, const char* msg, logger_levels log_level=log_level_default);
        void report(const char* tag, uint64_t val, bool hex=false);
        void reporti(const char* tag, int32_t val);
        void reportd(const char* tag, double val);
        void report(const char* tag, const char* msg);
        void report_long(const char* tag, const uint32_t msg[], uint16_t x, uint16_t y=0);

        inline logger_levels get_level(void) {
            return level;
        }
    protected:
        Logger(void) {}
        ~Logger(void) {}
    private:
        logger_levels level=log_level_default;
        static char message[LOGGER_MSG_LEN];
        static char num_buf[LOGGER_NUM_LEN];

	    void val_fmt(const char* tag, uint64_t val, bool hex);
        void int_fmt(const char* tag, int32_t val);
        void dbl_fmt(const char* tag, double val);
        void str_fmt(const char* tag, const char* msg);
        void msg_fin(const char* mesg);
};

extern Logger& lg;

#endif // LOGGER_H
