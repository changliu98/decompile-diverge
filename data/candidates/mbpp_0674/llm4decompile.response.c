char *func0(char *string)
{
    char *str = strdup(string);
    if (str == NULL)
        return NULL;

    char *unique[100];
    int unique_count = 0;

    char *token = strtok(str, " ");
    while (token != NULL) {
        int found = 0;
        for (int i = 0; i < unique_count; i++) {
            if (!strcmp(token, unique[i])) {
                found = 1;
                break;
            }
        }

        if (!found)
            unique[unique_count++] = token;

        token = strtok(NULL, " ");
    }

    size_t total_length = 0;
    for (int i = 0; i < unique_count; i++)
        total_length += strlen(unique[i]) + 1;

    char *result = malloc(total_length);
    if (result == NULL) {
        free(str);
        return NULL;
    }

    result[0] = '\0';
    for (int i = 0; i < unique_count; i++) {
        strcat(result, unique[i]);
        if (i < unique_count - 1)
            strcat(result, " ");
    }

    free(str);
    return result;
}