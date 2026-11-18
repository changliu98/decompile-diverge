void InvMat22(float *out, float *in) {
    float det = in[0] * in[3] - in[1] * in[2];
    
    out[0] = in[3] / det;
    out[1] = -in[1] / det;
    out[2] = -in[2] / det;
    out[3] = in[0] / det;
}