int func0(int *a, int *b, int n) {
    qsort(a, n, sizeof(int), cmp);
    qsort(b, n, sizeof(int), cmp);
    int i = 1, j = 1, k = 1, l = 0, m = 1;
    bool flag = false;
    while (1) {
        if (k < n) {
            flag = (l < n)? false : true;
        }
        if (flag == false) {
            break;
        }
        if (a[i] <= b[j]) {
            m++;
            i++;
            if (m > l) {
                l = m;
            }
        } else {
            m--;
            j++;
        }
    }
    return l;
}