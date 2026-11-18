int func0(int a, int b) {
    int i, j, k, l, m, n;
    int res = 0;

    for (i = 1, j = a;; i++, j = a * i) {
        if (j >= b)
            break;
        if (a % i == 0 && b % i == 0)
            res += i;
    }

    return res;
}