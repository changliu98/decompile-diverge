char *func0(char *s) {
    int len = strlen(s);
    char *result = (char *)malloc(2 * len + 1);
    if (result == NULL) {
        return NULL;
    }
    int i, j;
    for (i = 0; i < len;) {
        for (j = 0; j < len; j++) {
            if (s[i]!= s[len - 1 - j]) {
                result[i + j] = s[len - 1 - j];
            } else {
                break;
            }
        }
        if (j < len) {
            i += j + 1;
            continue;
        }
        for (j = i; j < len; j++) {
            result[i + j] = s[len - j - 1];
        }
        result[i + j] = '\0';
        return result;
    }
    return result;
}