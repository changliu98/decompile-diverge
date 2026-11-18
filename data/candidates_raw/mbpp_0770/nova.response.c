int func0(int n) {
    int i, j, k;
    int sum = 0;
    int cube = 0;

    for (i = 1;; i++) {
        if (i <= n) {
            j = i * 2 - 1;
            k = j * j * j;
            sum = sum + k;
        } else {
            break;
        }
    }
    return sum;
}