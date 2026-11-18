void cylinder(float r,float h,float *csa,float *tsa,float *vol)
{
    *csa = 2.0 * 3.14 * r * h / 4.0;
    *tsa = 2.0 * 3.14 * r * (h + r) / 4.0;
    *vol = 3.14 * r * r * h / 4.0;
}