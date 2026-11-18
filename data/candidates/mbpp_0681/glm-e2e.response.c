int func0(int n) {
    int p;
    if (n % 2 == 0) {
        p = 2;
    } else {
        for (int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) {
                p = i;
                return p;
            }
        }
        p = n;
    }
    return p;
}