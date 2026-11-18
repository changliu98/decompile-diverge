void initialize_temp(int *a, int *b) {
    int i = 9, j = 14;
    while (i >= 0) {
        b[j] = a[i];
        i--;
        j--;
    }
    while (j + 1!= 0) {
        j--;
        b[j] = 0;
    }
}