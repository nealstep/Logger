#ifndef LOGGER_H
#define LOGGER_H

#define LOGGER_MSG_LEN 128
#define LOGGER_NUM_LEN 16

void send(const char* msg);

enum logger_levels {
    logger_none,
    logger_error,
    logger_warning,
    logger_info,
    logger_debug
};

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
        void value(const char* tag, uint32_t val, bool hex=true, logger_levels log_level=logger_info);
        void report(const char* tag, uint32_t val, bool hex=true);
    protected:
        Logger(void) {}
        ~Logger(void) {}
    private:
        logger_levels level=logger_info;
        static char message[LOGGER_MSG_LEN];
        static char num_buf[LOGGER_NUM_LEN];

	void val(const char* tag, uint32_t val, bool hex);
        void finish(const char* mesg);
};

extern Logger& l;

#endif // LOGGER_H
