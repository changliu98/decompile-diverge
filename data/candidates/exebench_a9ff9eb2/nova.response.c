void ltox(unsigned int num, char *bf) {
    int i = 0;
    unsigned int n = num;
    const char *hex = "0123456789abcdef";
    while (1) {
        if (i > 8)
            break;
        bf[9 - i] = hex[n & 0xF];
        n >>= 4;
        i++;
    }
    bf[0] = '0';
    bf[1] = 'x';
    bf[10] = '\n';
    bf[11] = '\0';
}