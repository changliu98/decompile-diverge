char *func0(const char *str, char *dest) {
    int j = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (!isspace(str[i])) {
            dest[j++] = str[i];
        }
    }
    dest[j] = '\0';
    return dest;
}