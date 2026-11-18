void mlQuadBezier(float *x, float *y, float *z, float t, float *out) {
    out[0] = (1 - t) * (1 - t) * (1 - t) * x[0] +
             3 * (1 - t) * (1 - t) * t * x[1] +
             3 * (1 - t) * t * t * x[2] + t * t * t * x[3];
    out[1] = (1 - t) * (1 - t) * (1 - t) * y[0] +
             3 * (1 - t) * (1 - t) * t * y[1] +
             3 * (1 - t) * t * t * y[2] + t * t * t * y[3];
    out[2] = (1 - t) * (1 - t) * (1 - t) * z[0] +
             3 * (1 - t) * (1 - t) * t * z[1] +
             3 * (1 - t) * t * t * z[2] + t * t * t * z[3];
}