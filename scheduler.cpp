#include "development.h"
//////////////////////////////////////////////////////////////////////////////
#include "scheduler.h"

#define TAG "scheduler"

unsigned long lastSwitchTime = 0;
int jobIndex = 0;

void job1() { ESP_LOGD(TAG, "Enable charge point %d", 1); }
void job2() { ESP_LOGD(TAG, "Enable charge point %d", 2); }
void job3() { ESP_LOGD(TAG, "Enable charge point %d", 3); }
void job4() { ESP_LOGD(TAG, "Enable charge point %d", 4); }

// Array of job function pointers
void (*jobs[])() = { job1, job2, job3, job4 };

void runScheduler() {
    lastSwitchTime = millis();

    while (true) {
        // Run the two active jobs
        jobs[jobIndex]();
        jobs[(jobIndex + 1) % 4]();

        // Check if it's time to switch
        if (millis() - lastSwitchTime >= SWITCH_INTERVAL) {
            lastSwitchTime = millis();
            jobIndex = (jobIndex + 2) % 4;  // Rotate jobs round-robin
            ESP_LOGD(TAG, "New charging period...");
        }

        sleep(1);
    }
}

void setup() {
    ESP_LOGD(TAG,"Charging interval: %0.1fs", SWITCH_INTERVAL/1000.0);
}

void loop() {
    ESP_LOGD(TAG,"Start scheduler");
    runScheduler();
}
