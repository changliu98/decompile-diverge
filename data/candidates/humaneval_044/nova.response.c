void func0(int num, int base, char *buf) {
    int i = 0;
    int isNegative = false;
    if (num < 0) {
        isNegative = true;
    }

    while (num > 0) {
        int rem = num % base;
        buf[i++] = (rem > 9)? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    if (isNegative) {
        buf[i++] = '-';
    }

    buf[i] = '\0';

    reverse(buf, i);
}