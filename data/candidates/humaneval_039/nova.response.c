int func0(int n) {
    int a, b, c, d, e, f, g, h, i, j, k;
    a = 1;
    b = 2;
    for (i = 0; i < n; i++) {
        a = a + b;
        c = a;
        a = b;
        b = c;
        for (j = 1;; j++) {
            for (k = 1;; k++) {
                if (a * a > b) {
                    if (a % b == 0) {
                        d = 0;
                        break;
                    } else {
                        d = 1;
                        break;
                    }
                } else {
                    b = b + 1;
                }
            }
            if (d == 0) {
                break;
            }
        }
        if (i == n - 1) {
            e = a;
        }
    }
    return e;
}