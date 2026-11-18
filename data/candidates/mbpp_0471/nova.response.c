int func0(int *arr, int n, int m) {
    int i, j, k, l;
    i = 1;
    j = 0;
    while (j < n) {
        k = arr[j] % m;
        l = (k * i) % m;
        i = l;
        j++;
    }
    return i % m;
}