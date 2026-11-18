void summary(int arr[], int size, double *pos, double *neg, double *zero) {
    int p = 0, n = 0, z = 0;
    int i = 0;

    for (;;) {
        if (i >= size) break;
        if (arr[i] > 0) p++;
        else if (arr[i] < 0) n++;
        else z++;
        i++;
    }

    *pos = (double)p / (double)size;
    *neg = (double)n / (double)size;
    *zero = (double)z / (double)size;
}