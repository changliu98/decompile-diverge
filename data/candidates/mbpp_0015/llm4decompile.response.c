char **func0(char *text, int *count)
{
    char **result = NULL;
    *count = 0;

    int len = strlen(text);
    int i = 0;
    while (i < len) {
        if (!isspace((unsigned char)text[i])) {
            i++;
            continue;
        }

        int start = i;
        while (i < len && !isspace((unsigned char)text[i])) {
            i++;
        }
        int end = i;

        int substr_len = end - start;
        char *substr = malloc((size_t)(substr_len + 1));
        strncpy(substr, text + start, (size_t)substr_len);
        substr[substr_len] = '\0';

        size_t size = (*count + 1) * sizeof(char *);
        result = realloc(result, size);
        result[*count] = substr;
        (*count)++;
    }

    return result;
}