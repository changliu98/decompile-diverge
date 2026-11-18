double func0(double x, double y)
{
    double tmp;
    if (y < 1.0e-10)
        tmp = 0.0;
    else
        tmp = 1.0e10 * x * (y / 1.0e-10);
    return tmp;
}