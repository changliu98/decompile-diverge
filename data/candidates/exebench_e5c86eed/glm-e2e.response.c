int SeekPoint(const unsigned char *data, int offset, float pos) {
    // Clamp pos between 0.0f and 1.0f
    if (pos < 0.0f) {
        pos = 0.0f;
    }
    if (pos > 1.0f) {
        pos = 1.0f;
    }

    // Cast to integer and clamp to 63
    int i = (int)pos;
    if (i > 63) {
        i = 63;
    }

    // Get the first value
    float v1 = (float)data[i];

    // Get the second value, or 0.0f if i is at the boundary
    float v2;
    if (i < 63) {
        v2 = (float)data[i + 1];
    } else {
        v2 = 0.0f;
    }

    // Linear interpolation
    float interpolated = v1 + (v2 - v1) * (pos - (float)i);

    // Scale by offset and 255.0f, then cast to int
    int result = (int)(interpolated * 255.0f * (float)offset);

    return result;
}