#include "development.h"

#include <sys/time.h>
#include <cstddef>

unsigned int millis () {
    struct timeval t ;
    gettimeofday ( & t , NULL ) ;
    return t.tv_sec * 1000 + ( t.tv_usec + 500 ) / 1000 ;
}

#include <iostream>
#include <chrono>
#include <thread>

void sleep (int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(1));  // Simulate workload
}
