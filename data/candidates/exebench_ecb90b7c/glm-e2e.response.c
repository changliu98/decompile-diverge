void OsdGetBezierWeights(float t, float *w, float *dw, float *ddw) {
    float t2 = t * t;
    float tcomplement = 1.0f - t;
    float tcomplement2 = tcomplement * tcomplement;

    if (w) {
        w[0] = tcomplement2 * tcomplement;
        w[1] = 3.0f * tcomplement2 * t;
        w[2] = 3.0f * t2 * tcomplement;
        w[3] = t2 * t;
    }

    if (dw) {
        dw[0] = -3.0f * tcomplement2;
        dw[1] = 3.0f * tcomplement2 - 6.0f * t * tcomplement + 1.0f;
        dw[2] = 6.0f * t * tcomplement - 3.0f * t2;
        dw[3] = 3.0f * t2;
    }

    if (ddw) {
        ddw[0] = 6.0f * tcomplement;
        ddw[1] = 12.0f * t - 6.0f;
        ddw[2] = 6.0f - 12.0f * t;
        ddw[3] = 6.0f * t;
    }
}