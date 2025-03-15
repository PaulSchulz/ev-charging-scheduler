#include "development.h"
//////////////////////////////////////////////////////////////////////////////
#include "scheduler.h"

unsigned long lastSwitchTime = 0;
int jobIndex = 0;

void job1() { ESP_LOGD("debug", "Running Job %d", 1); }
void job2() { ESP_LOGD("debug", "Running Job %d", 2); }
void job3() { ESP_LOGD("debug", "Running Job %d", 3); }
void job4() { ESP_LOGD("debug", "Running Job %d", 4); }

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
            ESP_LOGD("debug", "Switching jobs...");
        }

        sleep(1);
    }
}

void setup() {

}

void loop() {
    runScheduler();
}
