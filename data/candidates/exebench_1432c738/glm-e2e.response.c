void OsdGetBoxSplineWeights(float u, float v, float* weights) {
    float u2 = u * u;
    float u3 = u2 * u;
    float u4 = u3 * u;
    float v2 = v * v;
    float v3 = v2 * v;
    float v4 = v3 * v;

    float w = 1.0f - u - v;
    float w2 = w * w;
    float w3 = w2 * w;
    float w4 = w3 * w;

    // weights[0]
    weights[0] = w4 + (1.0f / 6.0f) * w3 * u;

    // weights[1]
    weights[1] = w4 + (1.0f / 6.0f) * w3 * v;

    // weights[2]
    weights[2] = v4 + (1.0f / 6.0f) * v3 * w;

    // weights[3]
    weights[3] = v4 + (1.0f / 6.0f) * v3 * u;

    // weights[4]
    weights[4] = u4 + (1.0f / 6.0f) * u3 * v;

    // weights[5]
    weights[5] = u4 + (1.0f / 6.0f) * u3 * w;

    // weights[6]
    weights[6] = w4 + (1.0f / 6.0f) * w3 * v + (1.0f / 3.0f) * w2 * u * v + (1.0f / 2.0f) * w2 * u2 + u4 + (1.0f / 6.0f) * u3 * v + (1.0f / 3.0f) * u2 * w * v;

    // weights[7]
    weights[7] = v4 + (1.0f / 6.0f) * v3 * u + (1.0f / 3.0f) * v2 * w * u + (1.0f / 2.0f) * v2 * w2 + w4 + (1.0f / 6.0f) * w3 * u + (1.0f / 3.0f) * w2 * u * v;

    // weights[8]
    weights[8] = u4 + (1.0f / 6.0f) * u3 * w + (1.0f / 3.0f) * u2 * v * w + (1.0f / 2.0f) * u2 * v2 + v4 + (1.0f / 6.0f) * v3 * w + (1.0f / 3.0f) * v2 * u * w + (1.0f / 2.0f) * w2 * u * v + (1.0f / 3.0f) * w * u2 * v + (1.0f / 2.0f) * w2 * v2;

    // weights[9]
    weights[9] = v4 + (1.0f / 6.0f) * v3 * w + (1.0f / 3.0f) * v2 * u * w + (1.0f / 3.0f) * v * u2 * w + (1.0f / 3.0f) * v * u * w2 + v4 + (1.0f / 6.0f) * v3 * u + (1.0f / 3.0f) * v2 * u * w + (1.0f / 3.0f) * v * u2 * w + (1.0f / 3.0f) * v * u * w2 + u4 + (1.0f / 2.0f) * u2 * v2 + (1.0f / 2.0f) * w2 * v2;

    // weights[10]
    weights[10] = w4 + (1.0f / 6.0f) * w3 * u + (1.0f / 3.0f) * w2 * u * v + (1.0f / 3.0f) * w * u2 * v + (1.0f / 3.0f) * w * u * v2 + w4 + (1.0f / 6.0f) * w3 * v + (1.0f / 3.0f) * w2 * u * v + (1.0f / 3.0f) * w * u2 * v + (1.0f / 3.0f) * w * u * v2 + u4 + (1.0f / 2.0f) * u2 * v2 + (1.0f / 2.0f) * w2 * v2;

    // weights[11]
    weights[11] = u4 + (1.0f / 6.0f) * u3 * v + (1.0f / 3.0f) * u2 * w * v + (1.0f / 3.0f) * u * w2 * v + (1.0f / 3.0f) * u * w * v2 + u4 + (1.0f / 6.0f) * u3 * w + (1.0f / 3.0f) * u2 * w * v + (1.0f / 3.0f) * u * w2 * v + (1.0f / 3.0f) * u * w * v2 + v4 + (1.0f / 2.0f) * v2 * w2 + (1.0f / 2.0f) * u2 * v2;

    // Normalization loop
    for (int i = 0; i < 12; ++i) {
        weights[i] *= (1.0f / 12.0f);
    }
}