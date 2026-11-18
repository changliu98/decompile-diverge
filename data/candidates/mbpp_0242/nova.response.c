int func0(char *str) {
    int i;

    i = 0;
    while (str[i]) {
        i++;
        str++;
    }
    return (i);
}