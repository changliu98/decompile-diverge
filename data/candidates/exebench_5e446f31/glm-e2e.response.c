void copy2(char *dest, char *src) {
    while ((*dest = *src) != '\0') {
        dest++;
        src++;
    }
}