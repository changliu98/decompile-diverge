int func0(int *a, int *b) {
    int i, j, k;
    k = 9;
    j = 0;
    for (i = 0; i < k; i++) {
        if (a[i]!= 0) {
            j++;
            if (b!= 0)
                *b = a[i];
        }
    }
    return j;
}