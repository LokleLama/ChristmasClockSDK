#include "ChristmasClock.hpp"
#include <iostream>
#include "pico/stdlib.h"

#include "Receiver.hpp"

void countdown(uint n) {
    for (uint i = 0; i < n; i++) {
        std::cout<<n-i<<std::endl;
        sleep_ms(1000);
    }
}

int main() {
    stdio_init_all();

    countdown(4);
    
    ChristmasClock::ChristmasClock clock;
    ChristmasClock::Receiver recv(pio1);


    int err = clock.StartupChecks();

    while (err != 0) { sleep_ms(1000); }

    int next_update = 0;
    while (true) {
        auto tick = time_us_32();
        if(tick > next_update){
            recv.Receive();
            clock.Update();
            auto tock = time_us_32();
            //std::cout << "STATS(clock.Update):" << tock-tick << std::endl;
            next_update = tick + 1000000;
        }
        sleep_ms(10);
    }
    return 0;
}
