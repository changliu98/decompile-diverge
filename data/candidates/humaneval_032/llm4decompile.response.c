double func0(double *xs, int size)
{
    double value;
    double driv;
    double x_pow;
    double ans;
    int i;
    int j;

    ans = 0.0;

    value = xs[0];
    for (i = 1; i < size; i++) {
        x_pow = 1.0;
        for (j = 0; j < i; j++) {
            x_pow *= ans;
        }
        value += xs[i] * x_pow;
    }

    while (fabs(value) > 1e-10) {
        driv = 0.0;
        for (i = 1; i < size; i++) {
            x_pow = 1.0;
            for (j = 1; j < i; j++) {
                x_pow *= ans;
            }
            driv += i * xs[i] * x_pow;
        }
        ans -= value / driv;

        value = xs[0];
        for (i = 1; i < size; i++) {
            x_pow = 1.0;
            for (j = 0; j < i; j++) {
                x_pow *= ans;
            }
            value += xs[i] * x_pow;
        }
    }

    return ans;
}