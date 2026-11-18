int func0(int n, int m) {
    int i, j = 1;
    for (i = 0;; i++) {
        if (i >= n)
            break;
        j = (j * 2) % m;
    }
    return j;
}