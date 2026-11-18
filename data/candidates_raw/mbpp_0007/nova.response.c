char **func0(char *str) {
    char **arr;
    char *pch;
    char *str_copy;
    int i = 0;

    arr = (char **)malloc(sizeof(char *) * (strlen(str) / 2 + 1));
    str_copy = strdup(str);
    while ((pch = strtok(str_copy, " \t\n\r\v\f"))!= NULL) {
        char *pch_copy = pch;
        char *pch_copy_end = pch + strlen(pch) - 1;
        bool is_word = true;
        while (pch_copy <= pch_copy_end) {
            if (*pch_copy == '.' || *pch_copy == ',' || *pch_copy == '!' ||
                *pch_copy == '?' || *pch_copy == ':' || *pch_copy == ';') {
                is_word = false;
            }
            *pch_copy = '\0';
            pch_copy--;
        }
        if (is_word) {
            arr[i++] = strdup(pch);
        }
        str_copy = NULL;
    }
    arr[i] = NULL;
    free(str_copy);
    return arr;
}