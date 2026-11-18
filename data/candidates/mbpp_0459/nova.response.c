char *func0(char *s) {
    size_t len = strlen(s);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i, j;
    for (i = j = 0; i < len; i++) {
        if (!isspace(s[i])) {
            result[j++] = s[i];
        }
    }
    result[j] = '\0';

    return result;
}