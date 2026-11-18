int func0(int x, int v[], int n) {
    int i, j;
    int r;

    for (i = 0; i < n; i++) {
        if (v[i] == x) {
            for (j = 0; j < i; j++) {
                v[j] = v[i - j - 1];
            }
            v[0] = x;
            r = 0;
            break;
        } else {
            r = -1;
        }
    }

    return r;
}