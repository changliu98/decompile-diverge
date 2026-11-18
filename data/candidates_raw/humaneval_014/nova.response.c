char **func0(char **arr, int *size) {
    int i, arr_len = str_arr_len(arr);
    char **new_arr = (char **)malloc(sizeof(char *) * arr_len);
    new_arr[0] = (char *)malloc(sizeof(char));
    new_arr[0][0] = '\0';
    for (i = 0; i < arr_len; i++) {
        int len = strlen(new_arr[i]);
        new_arr[i] = (char *)realloc(new_arr[i], len + strlen(arr[i]) + 2);
        new_arr[i][len] = arr[i][0];
        new_arr[i][len + 1] = '\0';
        new_arr[i] = strcat(new_arr[i], arr[i] + 1);
    }
    free(new_arr[0]);
    *size = arr_len;
    return new_arr;
}