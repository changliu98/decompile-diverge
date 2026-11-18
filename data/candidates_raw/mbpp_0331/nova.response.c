int func0(int n) {
    int i, j = 0;
    for (i = 1;; i *= 2) {
        if (i > n + 1)
            break;
        if (n & i)
            j++;
    }
    return j;
}