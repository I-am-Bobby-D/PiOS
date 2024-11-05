#include "serial.h"
#include "rprintf.h"
#include "mmu.h"
#include "sd.h"
//sd_init
//sd_readblock(unsigned int lba, unsigned char *buffer, unsigned int num);
#include "fat.h"
//struct boot_sector, root_directory_entry, file
#define LOCKED 1

char glbl[128];


extern struct table_descriptor_stage1 L1table[512];


//extern void esp_printf(const func_ptr f_ptr, charptr ctrl, ...);

/*
//timer delay activity
unsigned long get_timer_count() {
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

/*unsigned int getEl(){
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

    //esp_printf(putc, "Current Exec Level is %d\r\n", el);
    //unsigned long timer_count = get_timer_count();
    //wait(1);

    fat_init();
    //mmu_on();
    mapPages(0,0);
    loadPageTable(L1table);

    while(1){}
}

