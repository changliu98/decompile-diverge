int func0(int *a, int *b, int n) {
    int i, j, k = 0;
    for (i = 0; i < n;) {
        for (j = 0; j < n;) {
            if (a[i] == j) {
                j++;
            } else {
                break;
            }
        }
        if (j >= n) {
            for (j = 0; j < n;) {
                if (a[i] == j) {
                    j++;
                } else {
                    break;
                }
            }
            if (j >= n) {
                b[k] = i;
                k++;
            }
        }
        i++;
    }
    return k + 1;
}