int func0(int *arr, int n) {
    int i, j, k, l, m, p, q, r, s, t;
    int max;

    if (n < 4) {
        max = -1;
    } else {
        for (i = 0; i < n - 3; i++) {
            for (j = i + 1; j < n; j++) {
                if (arr[i] < arr[j]) {
                    t = arr[i];
                    arr[i] = arr[j];
                    arr[j] = t;
                }
            }
        }
        p = arr[0];
        q = arr[1];
        r = arr[2];
        s = arr[n - 1];
        t = arr[n - 2];
        m = p * q * r;
        k = s * t * p;
        if (m > k) {
            max = m;
        } else {
            max = k;
        }
    }
    return max;
}