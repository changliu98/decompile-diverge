int func0(int n) {
    int i, j, k;
    k = 0;
    for (i = n; i > 0; i = i - 1) {
        if ((i & (i - 1)) == 0) {
            k = i;
            break;
        }
    }
    return k;
}