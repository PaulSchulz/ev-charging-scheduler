//////////////////////////////////////////////////////////////////////////////
#include "esphome.h"

#include "scheduler.h"

#define TAG "scheduler"
#define SCHEDULER_NAME "round-robin"

unsigned long lastSwitchTime = 0;
int jobIndex = 0;

#define activePoints 2
#define totalPoints 4
int activeIndex[activePoints]; // Only subset of charge points are ever active

//void job1() { ESP_LOGD(TAG, "Enable charge point %d", 1); }
//void job2() { ESP_LOGD(TAG, "Enable charge point %d", 2); }
//void job3() { ESP_LOGD(TAG, "Enable charge point %d", 3); }
//void job4() { ESP_LOGD(TAG, "Enable charge point %d", 4); }

// Array of job function pointers
//void (*jobs[])() = { job1, job2, job3, job4 };

void charge_status(int* activeIndex) {
    ESP_LOGD(TAG, "Status");
    for (int i=0; i<activePoints; i++) {
        // Allocate initial active charge points
        ESP_LOGD(TAG, "  Active: %d", activeIndex[i]);
    }
}

void charge_start(int n) { ESP_LOGD(TAG, "  Start charge point %d", n); }
void charge_stop(int n) { ESP_LOGD(TAG, "  Stop charge point %d", n); }

void scheduler_setup() {
    ESP_LOGD(TAG, "Initial Setup");

    // Turn off all points
    ESP_LOGD(TAG, "Turn off all points");
    for(int i=0; i<totalPoints; i++) {
        charge_stop(i);
    }

    // Turn on initial active points
    for(int i=0; i<activePoints; i++) {
        activeIndex[i] = i;
        charge_start(activeIndex[i]);
    }
    charge_status(activeIndex);
}

void scheduler_run() {
    lastSwitchTime = millis();

    while (true) {
        // Run the two active jobs
        // jobs[jobIndex]();
        // jobs[(jobIndex + 1) % 4]();

        // charge_status(activeIndex);
        // Check if it's time to switch
        if (millis() - lastSwitchTime >= SWITCH_INTERVAL) {
            ESP_LOGD(TAG, "New charging interval: %0.1fs", SWITCH_INTERVAL/1000.0);
            lastSwitchTime = millis();
            // jobIndex = (jobIndex + 2) % 4;  // Rotate jobs round-robin

            for(int i=0; i<activePoints; i++) {
                charge_stop(activeIndex[i]);
                activeIndex[i] = (activeIndex[i] + activePoints) % totalPoints;
                charge_start(activeIndex[i]);
            }
            charge_status(activeIndex);
        }

        // Periodiic Status Updates


        sleep(1);
    }
}

void setup() {
    ESP_LOGD(TAG,"Scheduler: %s", SCHEDULER_NAME);
    ESP_LOGD(TAG,"Charging interval: %0.1fs", SWITCH_INTERVAL/1000.0);
    scheduler_setup();
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
