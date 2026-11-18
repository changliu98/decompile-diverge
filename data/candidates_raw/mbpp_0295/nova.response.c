int func0(int n) {
    int i, j = 1;
    for (i = 2; i < n; i++) {
        if (n % i == 0) {
            j = j + i;
        } else {
            continue;
        }
    }
    return j;
}