int func0(int n, int b, int m) {
    if (b > n - b) {
        b = n - b;
    }
    int arr[b + 1];
    for (int i = 0; i <= b; i++) {
        arr[i] = 0;
    }
    arr[1] = 1;
    for (int i = 1; i <= n; i++) {
        int j = (i < b) ? i : b;
        while (j > 0) {
            arr[j] = (arr[j] + arr[j - 1]) % m;
            j--;
        }
    }
    return arr[b];
}