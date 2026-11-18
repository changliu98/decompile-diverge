int func0(int *arr, int n, int p) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if ((arr[i] * arr[i]) % p == 1) {
            count++;
        }
    }
    return count;
}