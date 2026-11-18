void
compute_geometry(float r, float h, float *b, float *l, float *w)
{
    *b = 2.0 * r * h * 22.0 / 7.0 / 7.0;
    *l = 2.0 * r * (h + r) * 22.0 / 7.0 / 7.0;
    *w = r * r * h * 22.0 / 7.0 / 7.0;
}