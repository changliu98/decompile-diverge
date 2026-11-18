char **func0(char *s) {
    int count = 1;
    char *ptr = s;
    
    while (*ptr != '\0') {
        if (*ptr == ' ') {
            count++;
        }
        ptr++;
    }
    
    char **result = malloc((count + 1) * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }
    
    char *dup = strdup(s);
    if (dup == NULL) {
        free(result);
        return NULL;
    }
    
    int i = 0;
    char *token = strtok(dup, " ");
    while (token != NULL) {
        result[i] = strdup(token);
        i++;
        token = strtok(NULL, " ");
    }
    result[i] = NULL;
    
    free(dup);
    return result;
}