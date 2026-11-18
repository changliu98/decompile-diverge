char *func0(char *dest, const char *src) {
    do {
        *dest = *src;
        if (*dest == '\0')
            return dest;
        dest++;
        src++;
    } while (1);
}