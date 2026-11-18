void test_mean2(double *avg, double *numbers, int count) {
    double sum = 0.0;
    double sum2 = 0.0;
    int i = 0;

    for (i = 0; i < 2 * count; i += 2) {
        sum += numbers[i];
    }

    for (i = 1; i < 2 * count; i += 2) {
        sum2 += numbers[i];
    }

    avg[0] = sum / count;
    avg[1] = sum2 / count;
}