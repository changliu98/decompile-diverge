int func0(int *arr, int n) {
    int min_index = -1;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            min_index = i;
        }
    }
    return min_index;
}