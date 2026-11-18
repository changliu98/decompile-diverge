char* int2str(int num, char* buf, int base) {
    char temp[33];
    memset(temp, 0, 33);
    
    char* p = temp;
    char* q = buf;
    int n = num;
    
    if (base < 2 || base > 36) {
        buf[0] = '\0';
        return buf;
    }
    
    n = num;
    if (num < 0 && base == 10) {
        n = -num;
    }
    
    do {
        *p++ = tab[n % base];
        n /= base;
    } while (n != 0);
    
    if (num < 0 && base == 10) {
        *p++ = '-';
    }
    
    p--;
    
    char c;
    do {
        c = *p;
        *q++ = c;
        p--;
    } while (c != '\0');
    
    return buf;
}