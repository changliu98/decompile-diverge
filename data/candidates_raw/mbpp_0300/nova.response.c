double func0(int n) {
    int i;
    double a, b;

    a = 1.0;
    b = 1.0;
    for (i = 1;; i++) {
        if (i <= n) {
            a = a * (n + 1 - i) / i;
            b = b + a;
        } else
            break;
    }
    return b;
}