void func0(int n, int m, int k, int *x, int *y) {
    int i;
    *x = n;
    *y = n;
    for (i = 0;; i++) {
        if (i < k) {
            *y = *y - 1;
            *x = *x + 2;
        } else {
            break;
        }
    }
}