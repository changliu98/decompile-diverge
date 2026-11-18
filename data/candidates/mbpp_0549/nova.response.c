int func0(int n) {
    int i, j, k, l;
    i = 0;
    j = 0;
    for (k = 1;; k++) {
        if (k <= n) {
            i = (2 * k) - 1;
            j = j + (i * i * i * i);
        } else {
            break;
        }
    }
    return j;
}