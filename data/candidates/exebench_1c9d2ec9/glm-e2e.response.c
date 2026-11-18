void OsdGetBSplineWeights(float u, float *weight, float *deriv, float *deriv2) {
    // Constants loaded from memory
    const float oneSixth = 0.16666667f;  // 1/6
    const float oneThird = 0.33333334f;  // 1/3
    const float twoThirds = 0.66666669f; // 2/3
    const float oneHalf = 0.5f;          // 1/2
    const float one = 1.0f;
    const float threeHalves = 1.5f;      // 3/2
    const float three = 3.0f;
    const float six = 6.0f;
    const float twelve = 12.0f;

    float u2 = u * u;
    float u3 = u * u2;

    // Compute weights
    if (weight != NULL) {
        weight[0] = oneSixth * (three * u2 - three * u + 2.0f - u3);
        weight[1] = oneSixth * (six * u3 - twelve * u2 + six);
        weight[2] = oneSixth * (-three * u3 + three * u2 + three * u + 2.0f);
        weight[3] = oneSixth * u3;
    }

    // Compute first derivatives
    if (deriv != NULL) {
        deriv[0] = 0.5f * u2 + u - 1.5f;
        deriv[1] = -oneHalf * u - three * u2 + 3.0f;
        deriv[2] = 1.5f * u2 + u + 1.5f;
        deriv[3] = -3.0f * u2;
    }

    // Compute second derivatives
    if (deriv2 != NULL) {
        deriv2[0] = -u + 1.0f;
        deriv2[1] = 3.0f * u - 2.0f;
        deriv2[2] = -3.0f * u + 1.0f;
        deriv2[3] = u;
    }
}