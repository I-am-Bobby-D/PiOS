


char glbl[128];

void kernel_main() {

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
