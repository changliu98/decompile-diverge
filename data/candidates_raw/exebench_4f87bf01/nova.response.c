void func0(long long int *a, long long int *b) {
    long long int i = 0;
    while (1) {
        if (i < 4) {
            if (a[i] > (b[i] / 2) * 2)
                a[i] -= (b[i] / 2) * 2;
            i++;
        } else
            break;
    }
}