void pwm(double *array, int n, double *out, double offset, double scale, int mode) {
    double sum = 0.0;
    double w_sum = 0.0;
    double ww_sum = 0.0;

    if (offset == 0.0 && scale == 0.0) {
        for (int i = 1; i <= n; i++) {
            sum += array[i - 1];
            if (mode == 0) {
                w_sum += array[i - 1] * (n - i);
                ww_sum += array[i - 1] * (n - i) * (n - i - 1);
            }
            if (mode == 1) {
                w_sum += array[i - 1] * (i - 1);
                ww_sum += array[i - 1] * (i - 1) * (i - 2);
            }
        }
    } else {
        for (int i = 1; i <= n; i++) {
            sum += array[i - 1];
            double w = (i + offset) / (n + scale);
            if (mode == 0) {
                w_sum += array[i - 1] * (1.0 - w);
                ww_sum += array[i - 1] * (1.0 - w) * (1.0 - w);
            }
            if (mode == 1) {
                w_sum += array[i - 1] * w;
                ww_sum += array[i - 1] * w * w;
            }
        }
    }

    out[0] = sum / n;
    out[1] = w_sum / n / (n - 1);
    out[2] = ww_sum / n / ((n - 1) * (n - 2));
}