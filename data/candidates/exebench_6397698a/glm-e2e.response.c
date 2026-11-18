char* truncate_string_at_char(char* str, char c) {
    char* ptr = str;
    while (*ptr != '\0') {
        if (*ptr == c) {
            *ptr = '\0';
        }
        ptr++;
    }
    return str;
}