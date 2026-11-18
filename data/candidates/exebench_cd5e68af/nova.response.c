void merge(int *a, int *b, int *c) {
    int i = 0, j = 0, k = 0;
    while (1) {
        if (i < 7 && j < 7) {
            if (a[i] < b[j]) {
                c[k++] = a[i++];
            } else {
                c[k++] = b[j++];
            }
        } else if (i < 7) {
            c[k++] = a[i++];
        } else if (j < 7) {
            c[k++] = b[j++];
        } else {
            break;
        }
    }
}