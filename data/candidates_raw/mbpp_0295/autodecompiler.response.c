int d(int p) {
    int res = 1;
    int i = 2;
    while (1) {
        if (i >= p) break;
        if (p % i == 0) res += i;
        i++;
    }
    return res;
}