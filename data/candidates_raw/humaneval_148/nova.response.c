char **func0(char *str1, char *str2, int *n) {
    char *words[MAX_WORDS];
    int i, j, k, l;
    char **res;

    strcpy(sentence, str1);
    i = -1;
    j = -1;
    for (k = 0; k < MAX_WORDS; k++) {
        if (strcmp(words[k], str1) == 0)
            i = k;
        if (strcmp(words[k], str2) == 0)
            j = k;
    }
    if (i == -1 || j == -1 || i == j) {
        *n = 0;
        res = NULL;
    } else {
        if (i > j) {
            l = i;
            i = j;
            j = l;
        }
        *n = j - i - 1;
        if (*n < 1) {
            *n = 0;
            res = NULL;
        } else {
            res = (char **)malloc(*n * sizeof(char *));
            for (k = i + 1; k < j; k++)
                res[k - i - 1] = words[k];
        }
    }
    return res;
}