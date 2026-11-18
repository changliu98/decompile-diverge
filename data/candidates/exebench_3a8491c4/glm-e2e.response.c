void Calc_Sum_Mean(double *array, double *sum, double *mean) {
    *sum = 0.0;
    for (int i = 0; i < 100; i++) {
        *sum += array[i];
    }
    *mean = *sum / 100.0;
}