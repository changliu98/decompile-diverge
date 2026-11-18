void replace_char(char *str, char old_char, char new_char) {
    while (*str != '\0') {
        if (*str == old_char) {
            *str = new_char;
        }
        str++;
    }
}