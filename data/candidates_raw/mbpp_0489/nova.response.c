int func0(int n, int *a) {
    int i, j, k, l, m, max, min;
    max = a[0];
    min = a[0];
    for (i = 1;; i++) {
        if (i < n) {
            if (a[i] > max) {
                max = a[i];
                j = 1;
            } else if (a[i] == max) {
                j++;
            } else {
                continue;
            }
        } else {
            break;
        }
    }
    return j;
}