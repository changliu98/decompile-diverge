double KernelBessel_Q1(double x)
{
    int i;
    double p, q;

    p = 0.0370131719911558e-1;
    q = 1.0;
    for (i = 4; ; i--)
    {
        if (i < 0) break;
        p = p * (8.0 / x) * (8.0 / x) + KernelBessel_Q1.Pone[i];
        q = q * (8.0 / x) * (8.0 / x) + KernelBessel_Q1.Qone[i];
    }
    return (p / q);
}