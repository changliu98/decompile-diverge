char *sdscpylen(char *str, const char *format, size_t size) {
    char *result;

    if (strlen(str) < size) {
        result = str;
    } else {
        result = NULL;
    }

    if (result == NULL) {
        strncpy(str, format, size);
        str[size - 1] = '\0';
        result = realloc(str, size);
    }

    return result;
}