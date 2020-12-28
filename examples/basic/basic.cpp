#include <Arduino.h>

#include <Logger.h>

#define BAUD 115200
#define SERIAL_WAIT 50
#define WARMUP_WAIT 2000

void setup(void) {
    Serial.begin(BAUD);
    while (!Serial) delay(SERIAL_WAIT);
    delay(WARMUP);
}

void main(void) {
    l.error("Test Error");
    l.warn("Test Warn");
    l.info("Test Info");
    l.debug("Test Debug");
}

void send(const char* msg) {
    Serial.println(msg);
}