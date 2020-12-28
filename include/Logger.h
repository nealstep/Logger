#ifndef LOGGER_H
#define LOGGER_H

#define LOGGER_MSG_LEN 128
#define LOGGER_NUM_LEN 16
    
void send(const char* msg);

enum logger_levels {
    logger_none,
    logger_error,
    logger_warn,
    logger_info,
    logger_debug
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
        void value(const char* tag, uint32_t val, bool hex=true, logger_levels log_level=log_level_default);
        void value(const char* tag, const char* msg, logger_levels log_level=log_level_default);
        void report(const char* tag, uint32_t val, bool hex=true);
        void report(const char* tag, const char* msg);
    protected:
        Logger(void) {}
        ~Logger(void) {}
    private:
        logger_levels level=log_level_default;
        static char message[LOGGER_MSG_LEN];
        static char num_buf[LOGGER_NUM_LEN];

	    void val_fmt(const char* tag, uint32_t val, bool hex);
        void str_fmt(const char* tag, const char* msg);
        void msg_fin(const char* mesg);
};

extern Logger& lg;

#endif // LOGGER_H
