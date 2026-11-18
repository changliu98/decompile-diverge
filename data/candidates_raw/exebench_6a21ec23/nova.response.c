void func0(int *a, int n, int i, int j) {
    int k = 0;
    if (i > 0) {
        a[k++] = -i;
    }
    a[k++] = j + 1;
    a[k++] = -(n - i - j - 1);
    a[k] = 0;
}