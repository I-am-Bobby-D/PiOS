//#include "serial.h"
//#include "rprintf.h"
#include "mmu.h"
#define LOCKED 1

char glbl[128];


extern void mmu_on(void);
//timer delay activity
/*unsigned long get_timer_count() {
    volatile unsigned long* timer_count_register = (unsigned long*) 0x3f003000;
    return *timer_count_register;
}
*/
//timer delay activity
/*
void wait(unsigned int time){
    unsigned long start_time = get_timer_count();
    while (get_timer_count() - start_time < time){

    }
}
*/

//execution level activity
//broke upon changing execution level
/*
unsigned int getEl(){
    unsigned int el;
    asm ("mrs %0, CurrentEL" : "=r" (el)); //read reg
    return el >> 2;
}
*/
void kernel_main() {
//fix void (*)(int) cast for putc as arg

    //serial print activity
    //unsigned int el = getEl();
    /*doesn't take void functions for some reason, worked when putc returned an int, but broke upon change of execution level */

   // esp_printf(putc_wrapper, "Current Exec Level is %d\r\n", el);
    //unsigned long timer_count = get_timer_count();
    //wait(1);


 /*   extern int __bss_start, __bss_end;[
    char *bssstart, *bssend;

    bssstart = (char *)&__bss_start;
    bssend = (char *)&__bss_end;

    for (char *p = bssstart; p < bssend; ++p){
        *p = 0xFF;
    } */

    //mmu_on();
    mmu_on();

    while(1){
    }
}

