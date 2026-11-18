void OsdGetBSplineWeights(float x, float *c0, float *c1, float *c2)
{
    float one6th = 1.0f / 6.0f;
    float xsq = x * x;
    float xcub = x * xsq;

    *c0 = ((-3.0f * one6th - 1.0f) + (3.0f * one6th + 2.0f) * xsq - one6th * xcub) * one6th;
    *c1 = (((3.0f * one6th + 1.0f) - 3.0f * one6th * xsq) + one6th * xcub) * one6th;
    *c2 = ((-3.0f * one6th - 1.0f) + (-3.0f * one6th + 3.0f) * xsq) * one6th;
    *c3 = one6th * xcub;

    if (c1 != NULL) {
        *c1 = ((-1.0f - 2.0f * one6th) + (2.0f * one6th + 2.0f) * xsq) * one6th;
        *c2 = ((2.0f * one6th + 2.0f) - one6th * xsq) ^ (1 << 31);
        *c3 = ((-1.0f - one6th) + one6th * xsq) * one6th;
        *c0 = one6th * xsq;
    }
    if (c2 != NULL) {
        *c2 = (-1.0f + one6th) ^ (1 << 31);
        *c3 = (-2.0f - one6th) + one6th * x;
        *c0 = 1.0f + (-3.0f * one6th - 1.0f) * x;
        *c1 = x;
    }
}