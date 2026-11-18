long long func0(int n) {
    long long sum = 0;
    int i, j;
    for (i = 1;; i++) {
        if (i <= n) {
            j = 5 * i;
            sum = sum + (j * j * j * j * j);
        } else {
            break;
        }
    }
    return sum;
}