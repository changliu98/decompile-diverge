double computeEllipseArea(double a, double f)
{
    double b = sqrt(a * a + f * f);
    double LSA = 3.141592653589793238462643383279502884197169399375105820974944592 * a * b;
    return LSA;
}