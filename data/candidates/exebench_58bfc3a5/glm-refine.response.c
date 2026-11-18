void __cdecl FindDivDiff4Coeff(double a, double b, double c, double d, double e, double *dd)
{
    // Pack the 5 distinct points into an array for easier iteration
    const double x[5] = {a, b, c, d, e};

    // Calculate the 4th-degree divided difference coefficients
    for (size_t i = 0; i < 5; ++i)
    {
        double denom = 1.0;
        for (size_t j = 0; j < 5; ++j)
        {
            if (i != j)
            {
                denom *= (x[i] - x[j]);
            }
        }
        dd[i] = 1.0 / denom;
    }
}