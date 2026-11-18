void mct_encode_real(
    float c0,
    float c1,
    float c2,
    float* out)
{
    float yprime = c1 * (1.0f / sqrtf(2.0f));
    union { int i; float f; } u;
    u.f = c2;
    u.i ^= (1 << 31);
    float xprime = c0 + u.f * (1.0f / 2.0f);
    out[1] = c0 + c2;
    out[0] = xprime + yprime;
    out[2] = xprime - yprime;
}