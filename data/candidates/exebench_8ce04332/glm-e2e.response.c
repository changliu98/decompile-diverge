void int2str(int num, int divisor, char *str) {
    while (divisor != 0) {
        int digit = (num / divisor) % 10;
        *str++ = (char)(digit + '0');
        divisor /= 10;
    }
}