void ifft2pt(float *x, float alpha)
{
    float xr, xi, yr, yi;

    xr = x[0];
    xi = x[1];
    yr = x[2];
    yi = x[3];

    yr = xr + yr;
    yi = xi + yi;
    xr -= yr;
    xi -= yi;

    x[0] = alpha * yr;
    x[1] = alpha * yi;
    x[2] = alpha * xr;
    x[3] = alpha * xi;
}