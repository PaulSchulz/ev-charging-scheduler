#include "development.h"
#include "scheduler.h"

int main() {
    config();
    setup();
    while (true) {
        loop();
    }
    return 0;
}
