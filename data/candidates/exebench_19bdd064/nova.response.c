void ComputeAndOrientation(float *uv, float *out, float t) {
    out[0] = t;
    float u = uv[0];
    float v = uv[1];
    if (u < 0)
        u += 1;
    if (v < 0)
        v += 1;
    if (v >.5)
        u -= 1;
    if (u >.5)
        u -= 1;
    out[1] = u < 0? -1 : 1;
    out[2] = v <.5? v : 1 - v;
    if (v > 0 && v <.5)
        out[2] = -out[2];
}