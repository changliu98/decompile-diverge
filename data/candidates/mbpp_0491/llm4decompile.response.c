double func0(double a, int n, double r)
{
    double total;

    total = a*(1 - pow(r, n))/(1 - r);

    return total;
}