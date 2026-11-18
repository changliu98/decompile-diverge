void func0(int num, char *str) {
    while (num > 0) {
        if (num % 2 == 1) {
            *str = '1';
        } else {
            *str = '0';
        }
        num = num >> 1;
        str++;
    }
}