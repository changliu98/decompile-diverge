void func0(unsigned int num, char *buf) {
    int i = 9;
    while (i >= 0) {
        buf[i] = (num % 10) + '0';
        num /= 10;
        i--;
    }
    buf[10] = '\0';
}