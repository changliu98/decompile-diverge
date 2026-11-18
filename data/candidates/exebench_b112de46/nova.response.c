void af_filter_bilinear(float *a, float *b, float *c, float t, float *out) {
    float ta = 1.0 - t;
    float tb = t;
    float ca[3], cb[3];

    ca[0] = ta * a[0] + tb * b[0];
    ca[1] = ta * a[1] + tb * b[1];
    ca[2] = ta * a[2] + tb * b[2];

    cb[0] = ta * b[0] + tb * c[0];
    cb[1] = ta * b[1] + tb * c[1];
    cb[2] = ta * b[2] + tb * c[2];

    out[0] = ca[0] / cb[0];
    out[1] = ca[1] / cb[1];
    out[2] = ca[2] / cb[2];
}