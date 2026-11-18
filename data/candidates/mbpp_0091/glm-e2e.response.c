int func0(char **arr, char *str, int n) {
    for (int i = 0; i < n; i++) {
        if (strstr(arr[i], str) != NULL) {
            return 1;
        }
    }
    return 0;
}