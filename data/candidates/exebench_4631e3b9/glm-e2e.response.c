void c_decrypt(char *str) {
    while (*str != '\0') {
        int c = (signed char)*str - 13;
        if (c <= 0) {
            c += 256;
        }
        *str = (char)c;
        str++;
    }
}