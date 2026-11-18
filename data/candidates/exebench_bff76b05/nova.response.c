void project(int n, double *x, int *index) {
    int i;
    for (i = 0; i < n; i++) {
        if (index[i]!= 0)
            x[i] = -x[i];
    }
}