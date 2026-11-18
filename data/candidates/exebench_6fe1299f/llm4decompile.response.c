void quant_u(float *x,
                    int *ix,
                    float xmin,
                    float xmax,
                    int nlev)
{
    float step;
    float x0;
    int i;

    step = (xmax - xmin)/(float)(nlev - 1);

    x0 = xmin + 0.5*step;

    for (i = 0; i < nlev - 1; i++)
    {
        if (*x >= x0)
        {
            break;
        }
        x0 += step;
    }

    *x = xmin + i*step;
    *ix = i;
}