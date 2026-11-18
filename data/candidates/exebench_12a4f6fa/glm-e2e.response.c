void putoct(char *buf, short val) {
    char *p = buf + 7;
    buf[7] = '\0';
    p--;
    *p = '0' + (val & 7);
    
    while (p != buf) {
        val >>= 3;
        *--p = (val != 0) ? ('0' + (val & 7)) : ' ';
    }
}