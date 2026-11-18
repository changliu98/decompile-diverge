int func0(int n) {
    int i, j, k;
    for (i = 1, j = 0;; i *= 2) {
        if (n / i > 0) {
            k = j;
            j += n / i;
        } else
            break;
    }
    return j;
}