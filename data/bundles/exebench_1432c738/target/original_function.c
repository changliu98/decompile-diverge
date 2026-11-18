static inline
void
OsdGetBoxSplineWeights(float v, float w, float wP[12]) {

    float u = 1.0f - v - w;
# 177 "patchBasisCommon.h"
    float u2 = u*u;
    float u3 = u*u2;
    float u4 = u*u3;
    float v2 = v*v;
    float v3 = v*v2;
    float v4 = v*v3;
    float w2 = w*w;
    float w3 = w*w2;
    float w4 = w*w3;


    wP[ 0] = u4 + 2.0f*u3*v;
    wP[ 1] = u4 + 2.0f*u3*w;
    wP[ 8] = w4 + 2.0f*w3*u;
    wP[11] = w4 + 2.0f*w3*v;
    wP[ 9] = v4 + 2.0f*v3*w;
    wP[ 5] = v4 + 2.0f*v3*u;

    wP[ 2] = u4 + 2.0f*u3*w + 6.0f*u3*v + 6.0f*u2*v*w + 12.0f*u2*v2 +
                v4 + 2.0f*v3*w + 6.0f*v3*u + 6.0f*v2*u*w;
    wP[ 4] = w4 + 2.0f*w3*v + 6.0f*w3*u + 6.0f*w2*u*v + 12.0f*w2*u2 +
                u4 + 2.0f*u3*v + 6.0f*u3*w + 6.0f*u2*v*w;
    wP[10] = v4 + 2.0f*v3*u + 6.0f*v3*w + 6.0f*v2*w*u + 12.0f*v2*w2 +
                w4 + 2.0f*w3*u + 6.0f*w3*v + 6.0f*w3*u*v;

    wP[ 3] = v4 + 6*v3*w + 8*v3*u + 36*v2*w*u + 24*v2*u2 + 24*v*u3 +
                w4 + 6*w3*v + 8*w3*u + 36*w2*v*u + 24*w2*u2 + 24*w*u3 + 6*u4 + 60*u2*v*w + 12*v2*w2;
    wP[ 6] = w4 + 6*w3*u + 8*w3*v + 36*w2*u*v + 24*w2*v2 + 24*w*v3 +
                u4 + 6*u3*w + 8*u3*v + 36*u2*v*w + 24*u2*v2 + 24*u*v3 + 6*v4 + 60*v2*w*u + 12*w2*u2;
    wP[ 7] = u4 + 6*u3*v + 8*u3*w + 36*u2*v*w + 24*u2*w2 + 24*u*w3 +
                v4 + 6*v3*u + 8*v3*w + 36*v2*u*w + 24*v2*w2 + 24*v*w3 + 6*w4 + 60*w2*u*v + 12*u2*v2;

    for (int i = 0; i < 12; ++i) {
        wP[i] *= 1.0f / 12.0f;
    }
}