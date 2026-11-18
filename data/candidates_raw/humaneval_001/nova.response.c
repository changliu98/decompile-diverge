char **func0(char *str, int *size) {
    int i, j, k, l, m;
    char **arr;
    char *word;
    l = strlen(str);
    m = 0;
    k = 10;
    arr = (char **)malloc(k * sizeof(char *));
    word = (char *)malloc((l + 1) * sizeof(char));
    j = 0;
    *size = 0;
    for (i = 0; i < l; i++) {
        char c = str[i];
        if (c == '(') {
            m++;
            word[j++] = c;
        } else if (c == ')') {
            m--;
            word[j++] = c;
            if (m == 0) {
                word[j] = '\0';
                arr[*size] = (char *)malloc((strlen(word) + 1) * sizeof(char));
                strcpy(arr[(*size)++], word);
                if (*size >= k) {
                    k *= 2;
                    arr = (char **)realloc(arr, k * sizeof(char *));
                }
            }
        }
    }
    free(word);
    return arr;
}