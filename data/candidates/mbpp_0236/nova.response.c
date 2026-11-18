int func0(int n, int k) {
    int res;
    if (n < k)
        res = -1;
    else {
        int a = (n - k + 1) * (n - k + 2) / 2;
        int b = (n - 2 * k + 1) * (n - 2 * k + 2) / 2;
        res = a + b;
    }
    return res;
}