void __cdecl cylinder(float r, float h, float *csa, float *tsa, float *vol)
{
    // Curved Surface Area: 2 * PI * r * h
    *csa = 2.0f * PI * r * h;

    // Total Surface Area: 2 * PI * r * (h + r)
    *tsa = 2.0f * PI * r * (h + r);

    // Volume: PI * r^2 * h
    *vol = PI * (r * r) * h;
}