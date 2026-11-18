void peneira(int n, int *a) {
    int i, j, temp, k;
    i = 1;
    j = 2;
    temp = a[1];
    while (j <= n) {
        if (j < n && a[j] < a[j + 1])
            j++;
        if (temp < a[j]) {
            k = a[j];
            a[j] = a[i];
            a[i] = k;
            i = j;
            j = 2 * i;
        } else
            break;
    }
    a[i] = temp;
}