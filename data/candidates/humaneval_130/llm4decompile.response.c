int * func0(int n) {
    int * arr = (int *)malloc(sizeof(int) * (n + 1));
    arr[0] = 1;
    if (n == 0) {
        return arr;
    }
    arr[1] = 3;
    for (int i = 2; i <= n; i++) {
        if (i % 2 == 0) {
            arr[i] = i / 2 + 1;
        } else {
            arr[i] = arr[i - 1] + arr[i - 2] + (i + 1) / 2 + 1;
        }
    }
    return arr;
}