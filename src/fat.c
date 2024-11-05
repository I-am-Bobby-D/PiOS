#include "sd.h"
#include "fat.h"
#include "serial.h" //esp
#include "rprintf.h" //linked to esp

unsigned int root_sector;
char rde_region[2048];
char bootSector[512];
char fat_table[4096];
struct boot_sector *bs;
struct root_directory_entry *rde;

//string compare method accounting for spaces
int strCmp(char* a, char* b){
    int i = 0;
    while(a[i] != '\0' && b[i] != '\0') {
        //no spaces allowed
        if (a[i] == '\0' || b[i] == '\0') {
            return -1;
        }
        //differ?
        if (a[i] != b[i]){
            return -1;
        }
        i++;
    }
    //bruh if it got here you fucked up this method
    return 2;
}

int fat_init() {

    if (sd_init() != 0) {
        esp_printf(putc, "SD initialization error\n");
    }
    sd_readblock(0, (unsigned char*)bootSector, 1);
    bs = (struct boot_sector*)bootSector; //boot sector pointer




    //Validate the boot signature = 0xaa55
    if(bs->boot_signature != 0xaa55){
        //make sure your esp
        esp_printf(putc, "Invalid boot signature\n");
        return -1;
    }


    //Validate fs_type = "FAT12" using strCmp
    if(strCmp(bs->fs_type, "FAT12") == -1) {
        return -1;
    }

    // Print out some of the elements of the BIOS information block using rprintf...
    esp_printf(putc, "\n");
    esp_printf(putc, "bytes per sector = %d\n", bs->bytes_per_sector);
    esp_printf(putc, "sectors per cluster = %d\n", bs->num_sectors_per_cluster);
    esp_printf(putc, "reserved sectors = %d\n", bs->num_reserved_sectors);
    esp_printf(putc, "number of FATs = %d\n", bs->num_fat_tables);
    esp_printf(putc, "number of RDEs = %d\n", bs->num_root_dir_entries);

    // TODO: Read FAT table from the SD card into array fat_table
    sd_readblock((unsigned int)bs->num_reserved_sectors, (unsigned char*)fat_table, (unsigned int)(bs->num_fat_tables * bs->num_sectors_per_fat));

    // TODO: Compute root_sector as:
    // num_fat_tables + num_sectors_per_fat + num_reserved_sectors + num_hidden_sectors
    root_sector = (unsigned int)(bs->num_fat_tables + (bs->num_sectors_per_fat * bs->num_fat_tables));



    //(num_root_dir_entries*32)/512
    sd_readblock(root_sector, (unsigned char*)rde_region, (unsigned int)(bs->num_root_dir_entries*32)/512);

    return 0;
}


int fat_open(char* filename){
    struct root_directory_entry *rde;

    int i = 0;
    rde = (struct root_directory_entry*)rde_region[i];

    while(strCmp(rde->file_name, filename)) {
        if (i >= 2048) {
            esp_printf(putc, "File not contained in region.\n");
            return -1;
        }
        i++;
        rde = (struct root_directory_entry*)rde_region[i];
    }
    //search for files rde based on name
    //find filename, return cluster
    return 0;
}

int fat_read(char* buf, int n) {

    int clstr = ((int)rde->cluster)-2;
    sd_readblock(root_sector + (unsigned int)(((bs->num_root_dir_entries * 32) / 512) + (clstr * bs->num_sectors_per_cluster)), (unsigned char*)buf, (unsigned int)n);
    return 0;
}

