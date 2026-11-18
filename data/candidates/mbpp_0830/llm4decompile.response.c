double func0(double a, int digits)
{
    double d;
    double tmp;

    d = pow(10.0, -digits);
    tmp = ceil(a / d) * d * pow(10.0, digits);
    return round(tmp) / pow(10.0, digits);
}