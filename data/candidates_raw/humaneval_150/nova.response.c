int func0(int n, int a, int b) {
    int i, j, k, l, m, c = 1, d, e, f, g, h;
    if (n < 3) {
        h = 0;
    }
    for (i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            h = 0;
            break;
        } else {
            h = i + 1;
        }
    }
    if (h!= 0) {
        d = a;
    } else {
        d = b;
    }
    return d;
}