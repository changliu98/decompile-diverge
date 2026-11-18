void __cdecl prod_vet(float *x, float *y, float *z)
{
    // x[2] = x[0] * y[1] - y[0] * z[1]
    x[2] = (*x * y[1]) - (*y * z[1]);

    // y[2] = y[0] * z[1] - z[0] * x[1]
    y[2] = (*y * z[1]) - (*z * x[1]);

    // z[2] = z[0] * x[1] - x[0] * y[1]
    z[2] = (*z * x[1]) - (*x * y[1]);
}