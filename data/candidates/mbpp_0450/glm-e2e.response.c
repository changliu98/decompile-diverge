char **func0(char **arr, int n, int len, int *count) {
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (strlen(arr[i]) == len) {
            result[c++] = arr[i];
        }
    }
    *count = c;
    return result;
}