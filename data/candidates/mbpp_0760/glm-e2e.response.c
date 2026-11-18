const char *func0(int *arr, int n) {
    int i = 1;
    while (i < n) {
        if (arr[i] != arr[0]) {
            return "No";
        }
        i++;
    }
    return "Yes";
}