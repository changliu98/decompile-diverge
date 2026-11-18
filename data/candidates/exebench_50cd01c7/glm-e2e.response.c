void splini(int n, double *x, double *y, double *yp, double x0, double *ans) {
    double sum = 0.0;
    int i = 0;
    int j = 1;

    while (x0 > x[i] && j < n) {
        double xj = x[j];
        if (j < n - 1 && x[j] <= x0) {
            xj = x0;
        }

        double h = x[j] - x[i];
        double a = (x[j] - xj) / h;
        double b = (xj - x[i]) / h;
        double a2 = a * a;
        double b2 = b * b;

        // Evaluate the polynomial segment and its integral
        double term1 = (3.0 * a2 - 1.0) * y[i] / 6.0 + (3.0 * b2 - 1.0) * y[j] / 6.0;
        
        double c1 = (a2 * a - a) / 2.0 + a / 6.0;
        double c2 = (b2 * b - b) / 2.0 - b / 6.0;
        
        double term2 = (c1 * yp[i] + c2 * yp[j]) * h * h / 12.0;
        
        sum += (term1 + term2) * h;

        i++;
        j++;
    }

    *ans = sum;
}