void numconv(char *str) {
    while (*str != '\0') {
        *str = *str - 0x30; // 0x30 is the ASCII code for '0'
        str++;
    }
}