void int_to_str(int num, char *str) {
    int i = 9;
    while (i >= 0) {
        str[i] = (num % 10) + '0';
        num = num / 10;
        i--;
    }
    str[10] = '\0';
}