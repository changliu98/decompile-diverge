int func0(int *arr, int n, int lower, int upper) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] >= lower && arr[i] <= upper) {
            count++;
        }
    }
    return count;
}