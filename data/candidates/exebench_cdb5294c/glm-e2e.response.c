void int2str(int num, int base, char *str) {
    char *ptr = str;
    while (base != 0) {
        int digit = (num / base) % 10;
        *ptr = (char)(digit + '0');
        ptr++;
        base = base / 10;
    }
    *ptr = '\0';
}