void trim(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    str[i - 1] = '\0';
}