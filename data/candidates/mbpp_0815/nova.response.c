void func0(int *a, int n) {
    int i = 0, j = 0, k = n - 1, temp;
    while (j <= k) {
        if (a[j] == 0) {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j++;
        } else if (a[j] == 1) {
            j++;
        } else {
            temp = a[k];
            a[k] = a[j];
            a[j] = temp;
            k--;
        }
    }
}