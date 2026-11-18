char **func0(char *str, int n, int *size) {
    char **arr = (char **)malloc(sizeof(char *));
    char *word = NULL;
    int i = 0, j = 0, k = 0, l = 0;
    size_t len = strlen(str);

    while (i < len) {
        if (isspace(str[i]) || str[i] == '\0') {
            if (j == n) {
                arr[l][j] = '\0';
                arr = (char **)realloc(arr, sizeof(char *) * (l + 1));
                arr[l] = (char *)malloc(sizeof(char) * strlen(arr[l]));
                strcpy(arr[l], arr[l]);
                l++;
            }
            j = 0;
            i++;
        } else {
            arr[l][j] = str[i];
            if (ispunct(str[i])) {
                j++;
            }
        }
    }
    free(arr);
    *size = l;
    return arr;
}