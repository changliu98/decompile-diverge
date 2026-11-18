double frexp(double x, int *exp)
{
    int i = 0;
    double sign = 1.0;

    if (x < 0.0) {
        x = -x;
        sign = -1.0;
    }

    if (x != 0.0) {
        while (x >= 1.0) {
            ++i;
            x /= 2;
        }
        while (x < 0.5) {
            --i;
            x *= 2;
        }
    }
    *exp = i;

    return sign * x;
}