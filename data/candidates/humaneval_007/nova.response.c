char **func0(char **arr, int size, char *str, int *len) {
    char **new_arr = NULL;
    int i, j;
    for (i = 0, j = 0; i < size; i++) {
        if (strstr(arr[i], str)!= NULL) {
            new_arr = (char **)realloc(new_arr, (j + 1) * sizeof(char *));
            new_arr[j] = arr[i];
            j++;
        }
    }
    *len = j;
    return new_arr;
}