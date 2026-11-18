void char_replace(char *str, char old_char, char new_char) {
    if (*str == '\0') {
        return;
    }

    while (1) {
        str++;
        if (*str == '\0') {
            break;
        }
        if (*str == old_char) {
            *str = new_char;
        }
    }
}