int func0(int n, int k) {
    int sum;
    if (k >= 1) {
        sum = -(n - k) + func0(n, 0);
    } else if (k == 0) {
        sum = 0;
    } else if (k == 1) {
        sum = n;
    } else {
        sum = n + func0(n, k - 1);
    }
    return sum;
}