void ToRNA(char *str) {
    while (*str != '\0') {
        if (*str == 'T') {
            *str = 'U';
        } else if (*str == 't') {
            *str = 'u';
        }
        str++;
    }
}