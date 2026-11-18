void func0(int n, int *a, int *k) {
    int i, j, t, m = 10;
    *k = 1;
    *a = 1;
    while (n!= 1) {
        if (n % 2 == 1) {
            if (*k >= m) {
                m *= 2;
                a = (int *)realloc(a, m * sizeof(int));
            }
            a[(*k)++] = n;
            n = 3 * n + 1;
        } else
            n /= 2;
    }
    i = 1;
    while (i < *k) {
        t = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > t) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = t;
        i++;
    }
}