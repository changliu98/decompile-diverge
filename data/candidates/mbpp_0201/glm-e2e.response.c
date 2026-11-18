bool func0(const char **arr, int n) {
    for (int i = 1; i < n; i++) {
        if (strcmp(arr[0], arr[i]) != 0) {
            return false;
        }
    }
    return true;
}