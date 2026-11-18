int s390_cpumsf_reached_trailer(const unsigned char *addr, const unsigned char *buf) {
    long page_mask = (long)S390_CPUMSF_PAGESZ - 1;
    long trailer_entry = page_mask - ((long)buf & page_mask);
    
    if ((unsigned long)addr >= (unsigned long)trailer_entry) {
        return 1;
    } else {
        return 0;
    }
}