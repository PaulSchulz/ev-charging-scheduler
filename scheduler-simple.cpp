//////////////////////////////////////////////////////////////////////////////
#include "esphome.h"

#include "scheduler.h"

#define TAG "scheduler"
#define SCHEDULER_NAME "simple"

unsigned long lastSwitchTime = 0;
int jobIndex = 0;

void job1() { ESP_LOGD(TAG, "Enable charge point %d", 1); }
void job2() { ESP_LOGD(TAG, "Enable charge point %d", 2); }
void job3() { ESP_LOGD(TAG, "Enable charge point %d", 3); }
void job4() { ESP_LOGD(TAG, "Enable charge point %d", 4); }

// Array of job function pointers
void (*jobs[])() = { job1, job2, job3, job4 };

void scheduler_config() {
    ESP_LOGD(TAG,"Scheduler: %s", SCHEDULER_NAME);
    ESP_LOGD(TAG,"  Scheduling interval: %0.1fs", SWITCH_INTERVAL/1000.0);
}

void scheduler_run() {
    lastSwitchTime = millis();

    while (true) {
        // Run the two active jobs
        jobs[jobIndex]();
        jobs[(jobIndex + 1) % 4]();

        // Check if it's time to switch
        if (millis() - lastSwitchTime >= SWITCH_INTERVAL) {
            lastSwitchTime = millis();
            jobIndex = (jobIndex + 2) % 4;  // Rotate jobs round-robin
            ESP_LOGD(TAG, "New charging interval");
        }

        sleep(1);
    }
}

void config() {
    scheduler_config();
}

void setup() {

}

void loop() {
    ESP_LOGD(TAG,"Start scheduler");
    scheduler_run();
}

// class MyCustomComponent : public Component {
// public:
//
//     void setup() override {
//         ESP_LOGD(TAG,"setup()");
//     };
//
//     void loop() override {
//         ESP_LOGD(TAG,"loop()");
//     };
//
// } // class
