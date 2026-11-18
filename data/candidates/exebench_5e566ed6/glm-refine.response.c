int __cdecl fit_line(const double *x, const double *y, int count, double *a, double *b)
{
    double sum_x = 0.0;
    double sum_x2 = 0.0;
    double sum_y = 0.0;
    double sum_xy = 0.0;

    // Accumulate sums for the least squares formulas
    for (int i = 0; i < count; ++i)
    {
        sum_x  += x[i];
        sum_x2 += x[i] * x[i];
        sum_y  += y[i];
        sum_xy += x[i] * y[i];
    }

    // Calculate the denominator: n * sum(x^2) - (sum(x))^2
    double denom = (double)count * sum_x2 - sum_x * sum_x;

    // Check for division by zero (e.g., all x values are identical)
    if (denom == 0.0)
        return -1;

    // Calculate intercept (a) and slope (b)
    *a = (sum_y * sum_x2 - sum_x * sum_xy) / denom;
    *b = ((double)count * sum_xy - sum_x * sum_y) / denom;

    return 0;
}