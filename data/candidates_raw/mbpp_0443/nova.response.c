int func0(int *a, int n) {
    int max = a[0];
    int i = 0;
    while (i < n) {
        if (a[i] < max) {
            max = a[i];
        }
        i++;
    }
    return max;
}