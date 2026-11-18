static inline
void
OsdGetBSplineWeights(
    float t, float wP[4], float wDP[4], float wDP2[4]) {


    const float one6th = 1.0f / 6.0f;

    float t2 = t * t;
    float t3 = t * t2;

    wP[0] = one6th * (1.0f - 3.0f*(t - t2) - t3);
    wP[1] = one6th * (4.0f - 6.0f*t2 + 3.0f*t3);
    wP[2] = one6th * (1.0f + 3.0f*(t + t2 - t3));
    wP[3] = one6th * ( t3);


    if ((wDP)) {
        wDP[0] = -0.5f*t2 + t - 0.5f;
        wDP[1] = 1.5f*t2 - 2.0f*t;
        wDP[2] = -1.5f*t2 + t + 0.5f;
        wDP[3] = 0.5f*t2;
    }


    if ((wDP2)) {
        wDP2[0] = - t + 1.0f;
        wDP2[1] = 3.0f * t - 2.0f;
        wDP2[2] = -3.0f * t + 1.0f;
        wDP2[3] = t;
    }
}