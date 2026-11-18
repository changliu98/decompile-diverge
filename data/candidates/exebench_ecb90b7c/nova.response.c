void OsdGetBezierWeights(float t, float *a, float *b, float *c) {
    float t2 = t * t;
    float t3 = t * t2;
    float t4 = t * t3;

    a[0] = 10 * t3;
    a[1] = 15 * t4;
    a[2] = 6 * t3 * t2;
    a[3] = 6 * t4 * t;

    if (b!= NULL) {
        b[0] = 30 * t2;
        b[1] = 30 * t3;
        b[2] = 12 * t2 * t2;
        b[3] = 12 * t3 * t;
    }

    if (c!= NULL) {
        c[0] = 60 * t;
        c[1] = 60 * t2;
        c[2] = 24 * t * t;
        c[3] = 24 * t2;
    }
}