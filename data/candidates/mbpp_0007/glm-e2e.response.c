char** func0(char* str) {
    char** result = malloc((strlen(str) / 2 + 1) * sizeof(char*));
    int count = 0;
    char* copy = strdup(str);
    char* token = strtok(copy, " ");
    while (token != NULL) {
        char* end = token + strlen(token) - 1;
        while (end > token) {
            if (*end == '.' || *end == ',' || *end == '!' ||
                *end == '?' || *end == ';' || *end == ':') {
                *end = '\0';
                end--;
            } else {
                break;
            }
        }
        if (strlen(token) >= 4) {
            result[count] = strdup(token);
            count++;
        }
        token = strtok(NULL, " ");
    }
    result[count] = NULL;
    free(copy);
    return result;
}