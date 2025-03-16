// Macros used for development
#define ESP_LOGD(TAG, fmt, ...) printf("[%s] " fmt "\n", TAG, ##__VA_ARGS__)

unsigned int millis();
void sleep(int);

extern void config();
extern void setup();
extern void loop();
