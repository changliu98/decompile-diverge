void func0(char *str, int *x, int *y) {
    *y = str[0] - 'a';
    if (str[3] == '\0' || str[3] == '\n')
        *x = str[2] - '1';
    else
        *x = (str[2] - '0') * 10 + (str[3] - '0') - 1;
}