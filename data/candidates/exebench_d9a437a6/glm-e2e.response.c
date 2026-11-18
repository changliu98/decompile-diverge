unsigned long do_csum(const void *addr, int size, unsigned long csum) {
    if ((unsigned long)addr & 0x2) {
        csum += 1;
    }
    return csum;
}