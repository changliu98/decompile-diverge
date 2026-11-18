void func0(char num, char *buf) {
    int i;
    for (i = 7; i >= 0; i--) {
        buf[i] = (num & 1) + '0';
        num >>= 1;
    }
    buf[8] = '\0';
}