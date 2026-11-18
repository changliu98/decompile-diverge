void add_a_vector(double a, int n, double *x, double *y) {
    for (int i = n; i != 0; i--) {
        *y = *x * a + *y;
        x++;
        y++;
    }
}