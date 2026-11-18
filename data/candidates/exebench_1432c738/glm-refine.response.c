void __cdecl OsdGetBoxSplineWeights(float v, float w, float *wP)
{
    int i;
    float w3, w2, v3, v2, u3, u2, u;

    u = 1.0f - v - w;
    u2 = u * u;
    u3 = u * u * u;
    v2 = v * v;
    v3 = v * v * v;
    w2 = w * w;
    w3 = w * w * w;

    wP[0]  = 2.0f * u3 * v + u * u3;
    wP[1]  = 2.0f * u3 * w + u * u3;
    wP[8]  = 2.0f * w3 * u + w * w3;
    wP[11] = 2.0f * w3 * v + w * w3;
    wP[9]  = 2.0f * v3 * w + v * v3;
    wP[5]  = 2.0f * v3 * u + v * v3;

    wP[2] = 6.0f * v2 * u * w + 
            6.0f * v3 * u + 
            2.0f * v3 * w + 
            12.0f * u2 * v2 + 
            6.0f * u2 * v * w + 
            6.0f * u3 * v + 
            2.0f * u3 * w + 
            u * u3 + 
            v * v3;

    wP[4] = 6.0f * u2 * v * w + 
            6.0f * u3 * w + 
            2.0f * u3 * v + 
            12.0f * w2 * u2 + 
            6.0f * w2 * u * v + 
            6.0f * w3 * u + 
            2.0f * w3 * v + 
            w * w3 + 
            u * u3;

    wP[10] = 6.0f * w3 * u * v + 
             6.0f * w3 * v + 
             2.0f * w3 * u + 
             12.0f * v2 * w2 + 
             6.0f * v2 * w * u + 
             6.0f * v3 * w + 
             2.0f * v3 * u + 
             v * v3 + 
             w * w3;

    wP[3] = 12.0f * v2 * w2 + 
            60.0f * u2 * v * w + 
            6.0f * u * u3 + 
            24.0f * w * u3 + 
            24.0f * w2 * u2 + 
            36.0f * w2 * v * u + 
            8.0f * w3 * u + 
            6.0f * w3 * v + 
            24.0f * v * u3 + 
            24.0f * v2 * u2 + 
            36.0f * v2 * w * u + 
            8.0f * v3 * u + 
            6.0f * v3 * w + 
            v * v3 + 
            w * w3;

    wP[6] = 12.0f * w2 * u2 + 
            60.0f * v2 * w * u + 
            6.0f * v * v3 + 
            24.0f * u * v3 + 
            24.0f * u2 * v2 + 
            36.0f * u2 * v * w + 
            8.0f * u3 * v + 
            6.0f * u3 * w + 
            24.0f * w * v3 + 
            24.0f * w2 * v2 + 
            36.0f * w2 * u * v + 
            8.0f * w3 * v + 
            6.0f * w3 * u + 
            w * w3 + 
            u * u3;

    wP[7] = 12.0f * u2 * v2 + 
            60.0f * w2 * u * v + 
            6.0f * w * w3 + 
            24.0f * v * w3 + 
            24.0f * v2 * w2 + 
            36.0f * v2 * u * w + 
            8.0f * v3 * w + 
            6.0f * v3 * u + 
            24.0f * u * w3 + 
            24.0f * u2 * w2 + 
            36.0f * u2 * v * w + 
            8.0f * u3 * w + 
            6.0f * u3 * v + 
            u * u3 + 
            v * v3;

    for ( i = 0; i < 12; ++i )
        wP[i] = (1.0f / 12.0f) * wP[i];
}