int func0(int *arr, int n, int k) {
    int i = 0, j = 0;
    while (j < n) {
        if ((arr[j] * arr[j]) % k == 1) {
            i++;
        } else {
            j++;
        }
    }
    return i;
}