int func0(int *a, int n) {
    int i = 0, j, t;
    while (i < n) {
        for (j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                t = a[j];
                a[j] = a[i];
                a[i] = t;
            }
        }
        i++;
    }
    i = n - 1;
    while (i >= 0) {
        if (is_prime(a[i]) == 0) {
            t = a[i];
            break;
        } else
            i--;
    }
    return t;
}