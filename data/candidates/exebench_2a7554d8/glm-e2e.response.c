void replace(char *str, char old_char, char new_char) {
    char *ptr = strchr(str, old_char);
    while (ptr != NULL) {
        *ptr = new_char;
        ptr++;
        ptr = strchr(ptr, old_char);
    }
}