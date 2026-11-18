char **func0(char *str, int *size) {
    int i = 10, j = 0, k = 0, l = 0;
    char **arr = (char **)malloc(i * sizeof(char *));
    arr[0] = (char *)malloc((strlen(str) + 1) * sizeof(char));
    while (1) {
        if (str[l] == '\0')
            break;
        if (str[l] =='' || str[l] == ',') {
            if (k > 0) {
                arr[j][k] = '\0';
                arr[++j] = (char *)malloc((strlen(arr[j]) + 1) * sizeof(char));
                k = 0;
            }
            if (j >= i) {
                i *= 2;
                arr = (char **)realloc(arr, i * sizeof(char *));
            }
        } else
            arr[j][k++] = str[l];
        l++;
    }
    if (k > 0) {
        arr[j][k] = '\0';
        arr[++j] = (char *)malloc((strlen(arr[j]) + 1) * sizeof(char));
    }
    free(arr[j]);
    *size = j;
    return arr;
}