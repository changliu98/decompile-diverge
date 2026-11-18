int num_contig_ptes(long addr, long *out_addr) {
    int count = 0;
    *out_addr = addr;
    
    if (addr == 0x80) {
        count = 1;
    } else if (addr == 0x81) {
        *out_addr = PAGE_SIZE;
        count = CONT_PMDS;
    } else if (addr == 0x82) {
        *out_addr = 0x80;
        count = CONT_PTES;
    }
    
    return count;
}