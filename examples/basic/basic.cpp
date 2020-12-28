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
    ll_ind = 0;
    delay(WARMUP_WAIT);
}

void loop(void) {
    logger_levels ll;

    ll = ll_ar[ll_ind++];
    l.set_level(ll);
    Serial.print("Log Level:");
    Serial.println(ll);
    Serial.println("Error");
    l.error("Test Error");
    Serial.println("Warn");
    l.warn("Test Warn");
    Serial.println("Info");
    l.info("Test Info");
    Serial.println("Debug");
    l.debug("Test Debug");
    Serial.println("Value (warn)");
    l.value("zero", 0, logger_warn);
    l.value("str0", "only", logger_warn);
    Serial.println("Value (info)");
    l.value("one", 1);
    l.value("str1", "this");
    Serial.println("Report");
    l.report("two", 2);
    l.report("str2", "that");
    if (ll_ind  == LL_LEN) {
        ll_ind = 0;
    }

    delay(LOOP_WAIT);
}

void send(const char* msg) {
    Serial.println(msg);
}