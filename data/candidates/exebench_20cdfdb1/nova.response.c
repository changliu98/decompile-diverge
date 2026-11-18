void liefere_double_array_statistik(double *coeff, int n, double *max, double *min, double *sum,
                 double *avg) {
    *max = coeff[0];
    *min = coeff[0];
    *sum = 0;
    for (int i = 0; i < n; i++) {
        if (coeff[i] > *max)
            *max = coeff[i];
        if (coeff[i] < *min)
            *min = coeff[i];
        *sum += coeff[i];
    }
    *avg = *sum * 1.0 / n;
}