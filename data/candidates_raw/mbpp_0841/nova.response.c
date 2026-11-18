int func0(int *a, int n) {
    int i, j, count = 0;
    for (i = 0;; i++) {
        for (j = i + 1;; j++) {
            if (j >= n) {
                i = 0;
                break;
            }
            if (a[i] > a[j])
                count++;
        }
    }
    return count;
}