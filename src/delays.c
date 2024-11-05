#include "delays.h"
unsigned long get_timer_count() {
    volatile unsigned long* timer_count_register = (unsigned long*) 0x3f003000;
    return *timer_count_register;
}


//timer delay activity
void wait_msec(unsigned int time) {
    unsigned long start_time = get_timer_count();

    while(1) {
        if(start_time + (time*1000) <= get_timer_count()){
            return;
        }
    }
}

void wait_cycles(unsigned int cycles) {
    unsigned long tc = get_timer_count();

    while(1) {
        if(get_timer_count() >= tc + cycles) {
            return;
        }
    }
}
