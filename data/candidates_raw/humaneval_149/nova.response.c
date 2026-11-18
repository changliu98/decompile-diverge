char **func0(char **arr, int size, int *n) {
    int i, j;
    char **tmp;
    *n = 0;
    for (i = 0; i < size; i++) {
        if (strlen(arr[i]) % 2 == 0) {
            arr[*n] = arr[i];
            (*n)++;
        }
    }
    for (i = 0; i < *n; i++) {
        for (j = 0; j < *n - i - 1; j++) {
            if (strlen(arr[j]) > strlen(arr[j + 1]) ||
                (strlen(arr[j]) == strlen(arr[j + 1]) &&
                 strcmp(arr[j], arr[j + 1]) > 0)) {
                char *tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
    tmp = (char **)malloc(sizeof(char *) * (*n));
    for (i = 0; i < *n; i++) {
        tmp[i] = arr[i];
    }
    return tmp;
}