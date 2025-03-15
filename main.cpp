#include "development.h"
#include "scheduler.h"

int main() {
    setup();
    while (true) {
        loop();
    }
    return 0;
}
