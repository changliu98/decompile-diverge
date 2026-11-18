void calc_speed(double *y, double *dydt, double *f, double h) {
    int i, j, k;
    double y_temp, dydt_temp;

    for (i = 0; i < 19; i += 6) {
        for (j = 0; j < 3; j++) {
            k = i + j;
            y_temp = y[k] + h * f[k] / 6;
            dydt_temp = (y[k] + h * f[k] / 3 - h * dydt[k] / 3);
            y[k + 3] = y[k + 3] + (h * (dydt_temp + 2 * dydt[k + 3]) / 6);
        }
    }
}