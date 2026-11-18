int func0(int n, int *a) {
    int i, j, max, count;
    max = a[0];
    count = 1;
    for (i = 1;; i++) {
        if (i < n) {
            if (a[i] > max) {
                max = a[i];
                count = 1;
            } else if (a[i] == max) {
                count++;
            }
        } else {
            break;
        }
    }
    return count;
}