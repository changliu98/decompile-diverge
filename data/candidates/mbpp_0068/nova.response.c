int func0(int *arr, int n) {
    int i;
    bool asc = true, dsc = true;
    for (i = 0;; i++) {
        if (i >= n - 1)
            break;
        if (arr[i] > arr[i + 1])
            asc = false;
        if (arr[i] < arr[i + 1])
            dsc = false;
    }
    bool ans = asc || dsc;
    return ans % 2;
}