void itoa(unsigned int num, char *buf) {
    int i = 7;
    do {
        buf[i] = 0;
        buf[--i] = '0' + num % 10;
    } while (num /= 10);
}