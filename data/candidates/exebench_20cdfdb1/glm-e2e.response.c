void liefere_double_array_statistik(const double *array, int n, double *min, double *max, double *sum, double *avg) {
    if (n <= 0) {
        return;
    }

    *min = array[0];
    *max = array[0];
    *sum = 0.0;

    for (int i = 0; i < n; i++) {
        if (array[i] < *min) {
            *min = array[i];
        }
        if (array[i] > *max) {
            *max = array[i];
        }
        *sum += array[i];
    }

    *avg = *sum / (double)n;
}