void OsdGetBSplineWeights(float t, float wP[4], float wDP[4], float wDP2[4])
{
    float t2 = t * t;
    float t3 = t2 * t;

    wP[0] = (1.0f / 6.0f) * (1.0f - 3.0f * t + 3.0f * t2 - t3);
    wP[1] = (1.0f / 6.0f) * (4.0f - 6.0f * t2 + 3.0f * t3);
    wP[2] = (1.0f / 6.0f) * (1.0f + 3.0f * t + 3.0f * t2 - 3.0f * t3);
    wP[3] = (1.0f / 6.0f) * t3;

    if (wDP != NULL) {
        wDP[0] = t - 2.0f * t2 + t3;
        wDP[1] = 2.0f * t2 - 3.0f * t;
        wDP[2] = 1.0f - t + 2.0f * t2 - t3;
        wDP[3] = t2 * t;
    }

    if (wDP2 != NULL) {
        wDP2[0] = -1.0f + t;
        wDP2[1] = 2.0f * t - 3.0f;
        wDP2[2] = 1.0f - 3.0f * t;
        wDP2[3] = t;
    }
}