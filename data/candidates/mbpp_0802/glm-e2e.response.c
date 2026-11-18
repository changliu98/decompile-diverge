int func0(int *arr, int n) {
    int i = 1;
    while (i < n) {
        if (arr[i] < arr[i - 1]) {
            return i;
        }
        i++;
    }
    return 0;
}