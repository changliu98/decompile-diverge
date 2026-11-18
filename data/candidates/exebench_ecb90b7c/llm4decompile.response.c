void OsdGetBezierWeights( float t, float *wP, float *wDP, float *wDP2 )
{
    float t2 = t * t;
    float t3 = t2 * t;
    float m1 = 1.0f - t;
    float m2 = m1 * m1;
    float m3 = m2 * m1;


    wP[0] = m3;
    wP[1] = 3.0f * m2 * t;
    wP[2] = 3.0f * m1 * t2;
    wP[3] = t3;


    if( wDP )
    {
        wDP[0] = -3.0f * m2;
        wDP[1] = 3.0f * (2.0f * t2 - 3.0f * t + 1.0f);
        wDP[2] = 3.0f * (3.0f * t2 - 2.0f * t);
        wDP[3] = 3.0f * t2;
    }


    if( wDP2 )
    {
        wDP2[0] = 6.0f * m1;
        wDP2[1] = 6.0f * (-2.0f * t + 1.0f);
        wDP2[2] = 6.0f * (3.0f * t - 2.0f);
        wDP2[3] = 6.0f * t;
    }
}