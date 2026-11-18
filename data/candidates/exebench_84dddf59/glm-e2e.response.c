void ck_decrypt(char *str) {
    while (*str != '\0') {
        char c = *str;
        if (c != 'p' && c != '\\' && c != 'S') {
            *str = c ^ 0xf;
        }
        str++;
    }
}