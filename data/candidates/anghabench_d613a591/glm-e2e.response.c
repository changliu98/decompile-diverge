float _RGB(float t, float c1, float c2) {
    // Wrap t around if it's outside [0, 1]
    if (t < 0.0f) {
        t += 1.0f;
    } else if (t > 1.0f) {
        t -= 1.0f;
    }

    if (t < 1.0f / 6.0f) {
        // Interpolate between c1 and c2
        return c1 + (c2 - c1) * t * 6.0f;
    } else if (t >= 1.0f / 6.0f && t < 0.5f) {
        // Return the second color directly
        return c2;
    } else if (t >= 0.5f && t < 2.0f / 3.0f) {
        // Interpolate between c1 and c2 inversely
        return c1 + (c2 - c1) * (2.0f / 3.0f - t) * 6.0f;
    } else {
        // Return the first color directly
        return c1;
    }
}