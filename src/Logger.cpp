#include <Arduino.h>

#include <Logger.h>

Logger& l = Logger::get_instance();

char Logger::message[LOGGER_MSG_LEN];
char Logger::num_buf[LOGGER_NUM_LEN];

static const char err_str[] = "! ";
static const char inf_str[] = "* ";
static const char val_str[] = "^ ";
static const char sep_str[] = ":";
static const char hex_str[] = "0x";

void Logger::set_level(logger_levels new_level) {
    level = new_level;
}
void Logger::error(const char* msg) {
    if (level > logger_error) {
        return;
    }
    strcpy(message, err_str);
    finish(msg);
}

void Logger::info(const char* msg) {
    if (level > logger_info) {
        return;
    }
    strcpy(message, inf_str);
    finish(msg);
}

void Logger::val(const char* tag, uint32_t val, bool hex, logger_levels log_level) {
    size_t slen;
    
    if (level > log_level) {
        return;
    }
    strcpy(message, val_str);
    if (hex) {
        ltoa(val, num_buf, 16);
    } else {
        ltoa(val, num_buf, 10);
    }
    slen = LOGGER_MSG_LEN-3;
    strncat(message, tag, slen);
    slen -= strlen(tag);
    strncat(message, sep_str, slen);
    slen -= 1;
    if (hex) {
      strncat(message, hex_str, slen);
      slen -= 2;
    }
    strncat(message, num_buf, slen);
    send(message);  
}     

void Logger::finish(const char* msg) {
    strncat(message, msg, LOGGER_MSG_LEN-3);
    send(message);  
}
