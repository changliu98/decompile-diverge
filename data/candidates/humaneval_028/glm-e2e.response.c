char *func0(char **strs, int n) {
    int total_length = 0;
    for (int i = 0; i < n; i++) {
        total_length += strlen(strs[i]);
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    for (int i = 0; i < n; i++) {
        strcat(result, strs[i]);
    }

    return result;
}