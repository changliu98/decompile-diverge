char *strcpy(char *dest, const char *src) {
    char *original_dest = dest;
    const char *current_src = src;

    while (*current_src != '\0') {
        *dest++ = *current_src++;
    }

    *dest = '\0';

    return original_dest;
}