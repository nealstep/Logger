#include <Logger.h>

Logger& lg = Logger::get_instance();

char Logger::message[LOGGER_MSG_LEN];
char Logger::num_buf[LOGGER_NUM_LEN];

static const char err_str[] = "! ";
static const char wrn_str[] = "# ";
static const char inf_str[] = "* ";
static const char dbg_str[] = "% ";
static const char val_str[] = "^ ";
static const char rep_str[] = "$ ";
static const char sep_str[] = ":";
static const char hex_str[] = "0x";
static const char vlb_str[] = "( ";
static const char vlc_str[] = "- ";
static const char vle_str[] = ") ";
static const char prt_str[] = "& ";
static const char rlb_str[] = "{ ";
static const char rlc_str[] = "-";
static const char rle_str[] = "} ";

void Logger::set_level(logger_levels new_level) {
    level = new_level;
}

void Logger::error(const char* msg) {
    if (level < logger_error) {
        return;
    }
    strcpy(message, err_str);
    msg_fin(msg);
}

void Logger::warn(const char* msg) {
    if (level < logger_warn) {
        return;
    }
    strcpy(message, wrn_str);
    msg_fin(msg);
}

void Logger::info(const char* msg) {
    if (level < logger_info) {
        return;
    }
    strcpy(message, inf_str);
    msg_fin(msg);
}

void Logger::debug(const char* msg) {
    if (level < logger_debug) {
        return;
    }
    strcpy(message, dbg_str);
    msg_fin(msg);
}

void Logger::print(const char* msg) {
    strcpy(message, prt_str);
    msg_fin(msg);
}

void Logger::value(const char* tag, uint32_t val, logger_levels log_level, bool hex) {
    if (level < log_level) {
        return;
    }
    strcpy(message, val_str);
    val_fmt(tag, val, hex);
}

void Logger::value(const char* tag, const char* msg, logger_levels log_level) {
    if (level < log_level) {
        return;
    }
    strcpy(message, val_str);
    str_fmt(tag, msg);
}

void Logger::value_long(const char* tag, const char* msg, logger_levels log_level) {
    size_t slen;
    uint16_t i;
    uint8_t j;

    if (level < log_level) {
        return;
    }
      
    strcpy(message, vlb_str);
    slen = LOGGER_MSG_LEN-3;
    strncat(message, tag, slen);
    send(message);

    strcpy(message, vlc_str);
    j = 2;
    for (i=0;i<strlen(msg);i++) {
        message[j++] = msg[i];
        if ((msg[i] == '\n') || (j > (LOGGER_MSG_LEN-5))) {
            message[--j] = '\0';
            send(message);
            strcpy(message, vlc_str);
            j = 2;
        }
    }
    message[j] = msg[i];
    send(message);
    strcpy(message, vle_str);
    slen = LOGGER_MSG_LEN-3;
    strncat(message, tag, slen);
    send(message);
}

void Logger::report(const char* tag, uint32_t val, bool hex) {
    strcpy(message, rep_str);
    val_fmt(tag, val, hex);
}

void Logger::report(const char* tag, const char* msg) {
    strcpy(message, rep_str);
    str_fmt(tag, msg);
}

void Logger::report_long(const char* tag, const uint32_t msg[], uint16_t x, uint16_t y) {
    uint8_t u32_items_line, k;
    uint16_t i, j, el;
    size_t slen;
  
    u32_items_line = floor((LOGGER_MSG_LEN - 4) / 5);
    strcpy(message, rlb_str);
    slen = LOGGER_MSG_LEN-3;
    strncat(message, tag, slen);
    send(message);
    for (i=0;i<y;i++) {
        k = 0;
        strcpy(message, rlc_str);
        slen = LOGGER_MSG_LEN-2;
        for (j=0;j<x;j++) {
            if (k == u32_items_line) {
                //strncat(message, "\n", slen);
                send(message);
                k = 0;
                strcpy(message, rlc_str);
                slen = LOGGER_MSG_LEN-2;
                strncat(message, "  ", slen);
                slen -= 2;
            }
            el = (i * x) + j;
            sprintf(num_buf, " %04x", msg[el]);
            strncat(message, num_buf, slen);
            slen -= strlen(num_buf);
            k++;
        }
        //strncat(message, "\n", slen);
        send(message);
    }
    // print end
    strcpy(message, rle_str);
    slen = LOGGER_MSG_LEN-3;
    strncat(message, tag, slen);
    send(message);
}

void Logger::val_fmt(const char* tag, uint32_t val, bool hex) {
    size_t slen;
    
    if (hex) {
        if (val < 256) {
            sprintf(num_buf, "%02x", val);
        } else if (val < 65536) {
            sprintf(num_buf, "%04x", val);
        } else {
            sprintf(num_buf, "%08x", val);
        }
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
    message[LOGGER_MSG_LEN-1] = '\0';
    send(message);  
}     

void Logger::str_fmt(const char* tag, const char* msg) {
    size_t slen;
    
    slen = LOGGER_MSG_LEN-3;
    strncat(message, tag, slen);
    slen -= strlen(tag);
    strncat(message, sep_str, slen);
    slen -= 1;
    strncat(message, msg, slen);
    message[LOGGER_MSG_LEN-1] = '\0';
    send(message);  
}     

void Logger::msg_fin(const char* msg) {
    strncat(message, msg, LOGGER_MSG_LEN-3);
    message[LOGGER_MSG_LEN-1] = '\0';
    send(message);  
}
