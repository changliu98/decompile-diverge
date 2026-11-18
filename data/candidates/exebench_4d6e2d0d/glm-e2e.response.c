char *str_cpy(char *dest, const char *src) {
    char *original_dest = dest;
    char c;

    do {
        c = *src;
        src++;
        *dest = c;
        dest++;
    } while (c != '\0');

    return original_dest;
}