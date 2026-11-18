unsigned long scan_ulong(const char *src, unsigned long *dest) {
    unsigned long i = 0;
    unsigned long result = 0;
    
    while (src[i] - '0' < 10) {
        result = result * 10 + (src[i] - '0');
        i++;
    }
    
    *dest = result;
    return i;
}