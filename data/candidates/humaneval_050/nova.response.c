void func0(char *str, int shift) {
    int i;
    int shift_value;
    int len = strlen(str);

    i = 0;
    while (i < len) {
        shift_value = (str[i] - 'a' + shift) % 26;
        str[i] = 'a' + shift_value;
        i++;
    }
}