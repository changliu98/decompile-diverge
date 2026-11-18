void _itoa_dec(unsigned int num, char *buf) {
    for (int i = 0; i < 10; i++) {
        if (num != 0 || i == 0) {
            buf[9 - i] = "0123456789"[num % 10];
        } else {
            buf[9 - i] = ' ';
        }
        num /= 10;
    }
}