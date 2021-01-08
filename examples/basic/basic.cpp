#include <Arduino.h>

#include <Logger.h>

#define BAUD 115200
#define SERIAL_WAIT 50
#define WARMUP_WAIT 2000
#define LOOP_WAIT 5000

#define LL_LEN 5
logger_levels ll_ar[LL_LEN] = {logger_none, logger_error, logger_warn, logger_info, logger_debug};
uint8_t ll_ind;

void setup(void) {
    Serial.begin(BAUD);
    while (!Serial) delay(SERIAL_WAIT);
    lg.info("Starting");
    ll_ind = 0;
    delay(WARMUP_WAIT);
    lg.info("Started");
}

const char long_text[] =
"It was the best of times, it was the worst of times,\n"
"it was the age of wisdom, it was the age of foolishness,\n"
"it was the epoch of belief, it was the epoch of incredulity,\n"
"it was the season of Light, it was the season of Darkness";

void loop(void) {
    logger_levels ll;

    ll = ll_ar[ll_ind++];
    lg.set_level(ll);
    Serial.print("Log Level:");
    Serial.println(ll);
    Serial.println("Error");
    lg.error("Test Error");
    Serial.println("Warn");
    lg.warn("Test Warn");
    Serial.println("Info");
    lg.info("Test Info");
    Serial.println("Debug");
    lg.debug("Test Debug");
    Serial.println("Value (warn)");
    lg.value("zero", 0, logger_warn);
    lg.value("str0", "only", logger_warn);
    Serial.println("Value (info)");
    lg.value("one", 1);
    lg.value("str1", "this");
    Serial.println("Report");
    lg.report("two", 2);
    lg.report("str2", "that");
    if (ll_ind  == LL_LEN) {
        ll_ind = 0;
    }
    lg.value_long("Dickens", long_text);
    
    lg.info("Looping");
    delay(LOOP_WAIT);
}

void send(const char* msg) {
    Serial.println(msg);
}