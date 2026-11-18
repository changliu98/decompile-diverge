long long func0(int n) {
    int i;
    long long a, b, c;
    a = 1;
    b = 1;
    for (i = 1;; i++) {
        if (i <= n) {
            a = a * i;
            b = b * a;
        } else
            break;
    }
    return b;
}