#include <Arduino.h>

#include <Logger.h>

#define BAUD 115200
#define SERIAL_WAIT 50
#define WARMUP_WAIT 2000
#define LOOP_WAIT 5000

#define LL_LEN 5
logger_levels ll_ar[LL_LEN] = {logger_print, logger_error, logger_warn, logger_info, logger_debug};
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

const uint32 arr[192] = 
{11420, 18693, 19262, 25364, 64487, 42662, 56085, 26646, 34081, 6092, 24262,
 23378, 52909, 48445, 3051, 24123, 16411, 54653, 22251, 35417, 31846, 42312,
 55411, 65009, 49288, 52848, 54770, 30285, 54511, 61579, 19191, 19913, 8283,
 3972, 19131, 47082, 10792, 10253, 208, 60409, 12824, 43928, 18223, 7403, 728,
 6476, 21376, 39159, 12312, 30027, 27696, 6000, 60376, 52756, 14649, 25235,
 19032, 14062, 53539, 19439, 8259, 63608, 6044, 59758, 32110, 60607, 47406,
 1334, 6205, 65127, 50028, 15214, 32423, 40781, 5914, 32044, 64630, 18849,
 23353, 20994, 8561, 8444, 20912, 46896, 13580, 26865, 54591, 5917, 42204,
 39860, 25804, 19149, 16867, 50416, 25042, 49058, 22971, 51217, 6368, 49937,
 15517, 12528, 16046, 48326, 34241, 47568, 37804, 15077, 39400, 56344, 62527,
 18725, 14927, 17139, 16674, 44185, 46315, 3035, 35343, 53297, 48212, 4514,
 34632, 36564, 19346, 30884, 46596, 64712, 40613, 22301, 24684, 56434, 65010,
 58277, 9229, 62720, 65060, 33027, 15421, 3929, 45807, 35793, 11427, 59597,
 32658, 31168, 21729, 61832, 32041, 52287, 55720, 12402, 13951, 9844, 23597,
 19204, 596, 9161, 19845, 64724, 38906, 27509, 22750, 41966, 23840, 52756,
 20131, 31625, 7313, 25069, 18755, 59905, 28694, 63679, 5178, 61377, 1482,
 39062, 31792, 79, 7632, 16447, 5164, 15210, 29101, 35528, 64643, 27641, 52441,
 46255, 48129, 53640};


void loop(void) {
    logger_levels ll;

    ll = ll_ar[ll_ind++];
    lg.set_level(logger_debug);
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
    lg.value("zero", 0, logger_warn, false);
    lg.value("str0", "only", logger_warn);
    Serial.println("Value (info)");
    lg.value("one", 1);
    lg.value("str1", "this");
    lg.value("8", (uint8_t)13);
    lg.value("16", (uint16_t)134U);
    lg.value("32", (uint32_t)64219UL);
    lg.value("64", (uint64_t)4093867285ULL);
    lg.valued("f", 3.1415);
    lg.valuei("gi", -21);
    lg.valued("gd", -21);
    Serial.println("Report");
    lg.report("two", 2);
    lg.report("str2", "that");
    lg.report("8", (uint8_t)13);
    lg.report("16", (uint16_t)134U);
    lg.report("32", (uint32_t)64219UL);
    lg.report("64", (uint64_t)4093867285ULL);
    lg.reportd("f", 3.1415);
    lg.reporti("gi", -21);
    lg.reportd("gd", -21);
    if (ll_ind  == LL_LEN) {
        ll_ind = 0;
    }
    lg.value_long("Dickens", long_text);
    lg.report_long("Example", arr, 12, 16);

    lg.info("Looping");
    while (true) {
        delay(50);
    }
    delay(LOOP_WAIT);
}

void send(const char* msg) {
    Serial.println(msg);
}
