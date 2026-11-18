void get_bits_exp(double x, double *a, int *n)
{
    double l;

    if (((*(long *)&x) & 0x7ff0000000000000LL) == 0) {
        l = (x * (1 << 52)) * (1 << 52);
        *n = ((*(long *)&l) >> 52) - 1083;
        *a = x / ((l / (1 << 52)) / (1 << 52));
    } else {
        *n = ((*(long *)&x) >> 52) - 1023;
        *a = x / ((double)(1 << 52));
    }
}