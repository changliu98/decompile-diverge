void __cdecl xformSetTranslation(float *t, float tx, float ty)
{
    // Row 0
    t[0] = 1.0f;
    t[1] = 0.0f;
    t[2] = tx;

    // Row 1
    t[3] = 0.0f;
    t[4] = 1.0f;
    t[5] = ty;
}