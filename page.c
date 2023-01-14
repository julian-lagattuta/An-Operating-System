#include "page.h"
PageTableEntry page_table[1024];
PageDirectoryEntry4Kb page_directory[1024];

void initPageDirectoryEntry4Kb(PageDirectoryEntry4Kb* pde,uint32_t addr_dir,unsigned int perms ){
    *pde = addr_dir | perms;
}
// void initPageDirectoryEntry4Mb(PageDirectoryEntry4Mb* pde,uint32_t high_addr,unsigned int perms ){
//     pde->flags=(perms<<2)|0b10000011; 
//     pde->avl_low_addr = 0;

//     pde->high_addr = 0;
// }
// void initPageTableEntry(PageTableEntry* pte,uint32_t addr,unsigned int global,unsigned int perms){
//    pte->flags=(perms<<2)|0b10000011; 
//     pte->avl_low_addr = (addr>>8) & (~0xf);

//     pte->high_addr = addr>>16;

// }
extern void enablePaging(uint32_t pdir);
void setupPaging(){
    // memset(page_directory,sizeof(page_directory),0);

    // memset(page_table,sizeof(page_table),0);

    // initPageDirectoryEntry4Kb(&page_directory[0], &page_table[0],1);
    // volatile int uselss = 10;
    // initPageTableEntry(&page_table[0b0100000000],&uselss,0,0);
    // enablePaging();
    // while(1);

    uint32_t* ptable=0; 
    uint32_t addr = 0;
    for(int i =0;i<1024;i++){
        ptable[i] = addr|3;
        addr+=4096;
    }   
    uint32_t* pdir = 4096;
    pdir[0] = 4096;

    pdir[0] = ptable[0]|3;
    for(int i=1; i<1024; i++)
    {
    pdir[i] = 0 | 2; // attribute set to: supervisor level, read/write, not present(010 in binary)
    };
    enablePaging(pdir);
}
