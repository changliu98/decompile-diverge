int arrayFind(int key, int a[], int n) {
    int i, j;
    for (i = 0; i < n; ++i) {
        if (a[i] == key) {
            for (j = 0; j < i; ++j) {
                a[i-j] = a[i-j-1];
            }
            a[0] = key;
            return 0;
        }
    }
    return -1;
}