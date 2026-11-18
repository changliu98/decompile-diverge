char *func0(char *s) {
    size_t len = strlen(s);
    char *res = (char *)malloc(len + 1);
    if (res == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    for (;;) {
        while (j < len &&!isalnum(s[j])) {
            j++;
        }
        if (j >= len) {
            break;
        }
        res[i++] = s[j++];
    }
    res[i] = '\0';
    return res;
}