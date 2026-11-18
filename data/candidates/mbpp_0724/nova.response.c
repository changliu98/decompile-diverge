int func0(int a, int n) {
    int i = 1, j = 1, k = 0, l, m, p, q;
    while (1) {
        for (l = 0; l < n; l++) {
            for (m = 0; m < i; m++) {
                p = (a * j) + l;
                j = p % 10;
                p = p / 10;
                if (p > 0) {
                    j = p % 10;
                    p = p / 10;
                }
            }
        }
        if (p > 0) {
            j = p % 10;
            p = p / 10;
            i++;
        } else
            break;
    }
    q = 0;
    for (l = 0; l < i; l++) {
        q = q + j;
    }
    return q;
}