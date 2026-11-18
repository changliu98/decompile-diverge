void dec2bin(int n, char *str) {
    while (n > 0) {
        if (n & 1) {
            *str++ = '1';
        } else {
            *str++ = '0';
        }
        n >>= 1;
    }
}