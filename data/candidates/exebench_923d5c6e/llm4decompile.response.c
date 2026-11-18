void ne_pre_filter16_double(double *y, double *x, double *f)
{







    double t[16];
    int i;
    for (i = 0; i < 16; i++)
    {
        t[i] = (x[i] - x[i + 1]) / 2.0;
    }
    for (i = 0; i < 16; i++)
    {
        y[i] = x[i] - t[i];
    }
    for (i = 0; i < 16; i++)
    {
        t[i] = t[i] * f[i] / 32.0;
    }
    for (i = 0; i < 16; i++)
    {
        y[i] += t[15 - i];
    }
    for (i = 0; i < 16; i++)
    {
        t[i] = t[i] * f[15 - i] / 32.0;
    }
    for (i = 0; i < 16; i++)
    {
        y[i] += t[15 - i];
    }
    for (i = 0; i < 16; i++)
    {
        t[i] = t[i] * f[15 - i] / 32.0;
    }
    for (i = 0; i < 16; i++)
    {
        y[i] += t[15 - i];
    }
    for (i = 0; i < 16; i++)
    {
        t[i] = t[i] * f[15 - i] / 32.0;
    }
    for (i = 0; i < 16; i++)
    {
        y[i] += t[15 - i];
    }
    for (i = 0; i < 16; i++)
    {
        t[i] = t[i] * f[15 - i] / 32.0;
    }
    for (i = 0; i < 16; i++)
    {
        y[i] += t[15 - i];
    }
    for (i = 0; i < 16; i++)
    {
        t[i] = t[i] * f[15 - i] / 32.0;
    }
    for (i = 0; i < 16; i++)
    {
        y[i] += t[15 - i];
    }
    for (i = 0; i < 16; i++)
    {
        t[i] = t[i] * f[15 - i] / 32.0;
    }
    for (i = 0; i < 16; i++)
    {
        y[i] += t[15 - i];
    }
    for (i = 0; i < 16; i++)
    {
        t[i] = t[i] * f[15 - i] / 32.0;
    }
    for (i = 0; i < 16; i++)
    {
        y[i] += t[15 - i];
    }
    for (i = 0; i < 16; i++)
    {
        t[i] = t[i] * f[15 - i] / 32.0;
    }
    for (i = 0; i < 16; i++)
    {
        y[i] += t[15 - i];
    }
    for (i = 0; i < 16; i++)
    {
        t[i] = t[i] * f[15 - i] / 32.0;
    }
    for (i = 0; i < 16; i++)
    {
        y[i] += t[15 - i];
    }
    for (i = 0; i < 16; i++)
    {
        t[i] = t[i] * f[15 - i] / 32.0;
    }
    for (i = 0; i < 16; i++)
    {
        y[i] += t[15 - i];
    }
    for (i = 0; i < 16; i++)
    {
        t[i] = t[i] * f[15 - i] / 32.0;
    }
    for (i = 0; i < 16; i++)
    {
        y[i] += t[15 - i];
    }
    for (i = 0; i < 16; i++)
    {
        t[i] = t[i] * f[15 - i] / 32.0;
    }
    for (i = 0; i < 16; i++)
    {
        y[i] += t[15 - i];
    }
    for (i = 0; i < 16; i++)
    {
        t[i] = t[i] * f[15 - i] / 32.0;
    }
    for (i = 0; i < 16; i++)
    {
        y[i] += t[15 - i];
    }
    for (i = 0; i < 16; i++)
    {
        t[i] = t[i] * f[15 - i] / 32.0;
    }
    for (i = 0; i < 16; i++)
    {
        y[i] += t[15 - i];
    }
    for (i = 0; i < 16; i++)
    {
        t[i] = t[i] * f[15 - i] / 32.0;
    }
    for (i = 0; i < 16; i++)
    {
        y[i] += t[15 - i];
    }
    for (i = 0; i < 16; i++)
    {
        t[i] = t[i] * f[15 - i] / 32.0;
    }
    for (i = 0; i < 16; i++)
    {
        y[i] += t[15 - i];
    }
    for (i = 0; i < 16; i++)
    {
        t[i] = t[i] * f[15 - i] / 32.0;
    }
    for (i = 0; i < 16; i++)
    {
        y[i] += t[15 - i];
    }
    for (i = 0; i < 16; i++)
    {
        t[i] = t[i] * f[15 - i] / 32.0;
    }
    for (i = 0; i < 16; i++)
    {
        y[i] += t[15 - i];
    }
    for (i = 0; i < 16; i++)
    {
        t[i] = t[i] * f[15 - i] / 32.0;
    }
    for (i = 0; i < 16; i++)
    {
        y[i] += t[15 - i];
    }
    for (i = 0; i < 16; i++)
    {
        t[i] = t[i] * f[15 - i] / 32.0;
    }
    for (i = 0; i < 16; i++)
    {
        y[i] += t[15 - i];
    }
    for (i = 0; i < 16; i++)
    {
        t[i] = t[i] * f[15 - i] / 32.0;
    }
    for (i = 0; i < 16; i++)
    {
        y[i] += t[15 - i];
    }
    for (i = 0; i < 16; i++)
    {
        t[i]