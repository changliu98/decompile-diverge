void func0(unsigned int num, char *buf) {
    unsigned int i = 0;
    while (i < 10) {
        if (num == 0 && i == 0) {
            buf[9 - i] = '0';
        } else {
            buf[9 - i] = num % 10 + '0';
        }
        num /= 10;
        i++;
    }
}