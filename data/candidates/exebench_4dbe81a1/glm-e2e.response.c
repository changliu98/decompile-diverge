char *GO_strcpy(char *dest, const char *src) {
    char *original_dest = dest;
    char c;

    do {
        c = *src++;
        *dest++ = c;
    } while (c != '\0');

    return original_dest;
}