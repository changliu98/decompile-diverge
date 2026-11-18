char **func0(char *str, int *count)
{
    int len = strlen(str);
    char **out = malloc(len * sizeof(char *));
    char *current = malloc(len + 1);
    current[0] = '\0';
    for (int i = 0; i < len; i++) {
        current = realloc(current, strlen(current) + 2);
        current[strlen(current)] = str[i];
        current[strlen(current) + 1] = '\0';
        out[i] = malloc(strlen(current) + 1);
        strcpy(out[i], current);
    }
    free(current);
    *count = len;
    return out;
}