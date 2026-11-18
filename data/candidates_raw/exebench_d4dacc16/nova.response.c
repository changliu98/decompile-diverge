void func0(long long int a[], long long int *max, long long int *min) {
    int i = 1;
    while (1) {
        if (i >= 6)
            return;
        if (a[i] < *max)
            *max = a[i];
        if (a[i] > *min)
            *min = a[i];
        i++;
    }
}