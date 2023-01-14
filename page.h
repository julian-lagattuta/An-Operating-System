#include "stdos.h"

typedef uint32_t PageDirectoryEntry4Kb;

typedef  uint32_t PageDirectoryEntry4Mb;
typedef  uint32_t  PageTableEntry;
void initPageDirectoryEntry4Kb(PageDirectoryEntry4Kb* pde,uint32_t addr_dir,unsigned int perms );
void initPageDirectoryEntry4Mb(PageDirectoryEntry4Mb* pde,uint32_t high_addr,unsigned int perms );
void initPageTableEntry(PageTableEntry* pte,uint32_t addr,unsigned int global,unsigned int perms);
void setupPaging();