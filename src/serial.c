#include "serial.h"
//base address converted to pointer
#define MU_IO (*(volatile unsigned int*)0x3F215040)

void putc(int data){
    MU_IO = (unsigned int)(data);
}

//wrapper because rprintf appears to require a non void function
int putc_wrapper(int data){
    putc(data);
    return data;

}
