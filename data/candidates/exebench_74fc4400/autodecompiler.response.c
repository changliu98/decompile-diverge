static void rifft2pt(float *a, float w)
{
    float x0r, x0i, x1r, x1i, x2r, x2i;

    x2r = 2.0f;
    x0r = a[0];
    x0i = a[1];
    x1r = 2.0f * a[2];
    x1i = 2.0f * a[3];
    x2r = x0r + x0i;
    x2i = x0r - x0i;
    a[0] = x2r + x1r;
    a[1] = x2i - x1i;
    a[2] = x2r - x1r;
    a[3] = x2i + x1i;
    a[0] *= w;
    a[1] *= w;
    a[2] *= w;
    a[3] *= w;
}