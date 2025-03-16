#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <iostream>
#include <chrono>
#include <thread>

// Function to get the current time in milliseconds
// extern unsigned long millis();

// Function to execute jobs and manage switching
// void runScheduler();

// Expose global variables for testing
extern unsigned long lastSwitchTime;
extern int jobIndex;

// Expose the switch interval
const unsigned long SWITCH_INTERVAL = 5000;  // 5 seconds for testing

#endif // SCHEDULER_H
