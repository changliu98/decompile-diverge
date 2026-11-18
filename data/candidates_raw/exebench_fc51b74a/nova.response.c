void func0(int i, int *p, int j) {
    if (j % 2 == 0) {
        long int k = i - 1;
        if (k >= 0 && k <= 7) {
            *p = *(arr + k);
        } else {
            *(p + 0) = -3;
        }
    } else {
        long int k = i - 1;
        if (k >= 0 && k <= 7) {
            *(p + 1) = -3;
        } else {
            *(p + 2) = -3;
        }
    }
}