char *byte2bin(char n, char *s) {
    int i = 0;
    while (i < 8) {
        if ((n & (1 << (7 - i)))!= 0)
            s[i] = '1';
        else
            s[i] = '0';
        i++;
    }
    s[8] = '\0';
    return s;
}