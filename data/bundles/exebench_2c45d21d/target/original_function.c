char last_char(char *ptr) {
    char c;

    if (ptr == NULL || *ptr == '\0') {
        return '\0';
    }

    while (*ptr != '\0') {
        ptr++;
    }
    ptr--;

    c = *ptr;
    *ptr = 0;
    return c;
}