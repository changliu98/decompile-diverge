int func0(int *arr, int n) {
    sortArray(arr, n);
    int count = 0;
    int max_count = 0;
    int min_count = n;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] == arr[i + 1]) {
            count++;
        } else {
            max_count = max_count > count ? max_count : count;
            min_count = min_count < count ? min_count : count;
            count = 0;
        }
    }
    return max_count - min_count;
}