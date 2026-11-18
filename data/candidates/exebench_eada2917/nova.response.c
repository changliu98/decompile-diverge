int HPCC_factor235(int n, int *a) {
    a[0] = 0;
    a[1] = 0;
    a[2] = 0;
    int i;
    while (n % 2 == 0) {
        a[0]++;
        n = n / 2;
    }
    while (n % 3 == 0) {
        a[1]++;
        n = n / 3;
    }
    while (n % 5 == 0) {
        a[2]++;
        n = n / 5;
    }
    return n == 1;
}