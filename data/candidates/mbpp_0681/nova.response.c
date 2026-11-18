int func0(int n) {
    int i, j;
    if (n % 2 == 0) {
        j = 2;
    } else {
        for (i = 3; i * i <= n; i += 2) {
            if (n % i == 0) {
                j = i;
                break;
            }
        }
        if (j == 0) {
            j = n;
        }
    }
    return j;
}