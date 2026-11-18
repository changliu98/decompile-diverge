int decToBin(unsigned int n, int *v) {
    int i, j, k, l;

    i = 1;
    j = 0;
    k = 0;
    while (1) {
        if (k > n) {
            n = n * 2;
            j++;
        } else {
            n = n / 2;
            j--;
        }
        k = j;
        if (k < 0) {
            if (n - i >= 0) {
                n = n - i;
                v[j - k] = 1;
            } else {
                v[j - k] = 0;
            }
            i = i / 2;
            k++;
        }
    }
    return j;
}