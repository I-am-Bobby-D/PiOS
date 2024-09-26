


char glbl[128];

unsigned long get_timer_count() {
    unsigned long* timer_count_register = (unsigned long*) 0x3f003000;
    return *timer_count_register;
}

void wait(unsigned int time){
    unsigned long start_time = get_timer_count();
    while (get_timer_count - start_time < time){

    }
}
void kernel_main() {

    unsigned long timer_count = get_timer_count();

    extern int __bss_start, __bss_end;
    char *bssstart, *bssend;

    bssstart = (char *)&__bss_start;
    bssend = (char *)&__bss_end;

    for (char *p = bssstart; p < bssend; ++p){
        *p = 0xFF;
    }
    while(1){
    }
}

