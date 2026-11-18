void rifft2pt(float *ioptr, float scale)
{
    float xi, yi, xr, yr;
    float xri, yri, xii, yii;

    xr = ioptr[0];
    xi = ioptr[1];
    yr = ioptr[2] * 0.5;
    yi = ioptr[3] * 0.5;

    xri = xr + yr;
    xii = xi - yi;
    yri = xr - yr;
    yii = xi + yi;

    ioptr[0] = xri * scale;
    ioptr[1] = xii * scale;
    ioptr[2] = yri * scale;
    ioptr[3] = yii * scale;
}