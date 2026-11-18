void RGBtoHSV(float r, float g, float b, float *h, float *s, float *v) {
    float max_val;
    float min_val;
    float delta;

    // Calculate max(r, g, b)
    if (g > b) {
        max_val = (r > g) ? r : g;
    } else {
        max_val = (r > b) ? r : b;
    }

    // Calculate min(r, g, b)
    if (g < b) {
        min_val = (r < g) ? r : g;
    } else {
        min_val = (r < b) ? r : b;
    }

    *v = max_val;
    delta = max_val - min_val;

    if (max_val == 0.0f) {
        *s = 0.0f;
        *h = 0.0f; // 0xc77(%rip) points to 0.0f
        return;
    }

    *s = delta / max_val;

    if (r == max_val) {
        *h = (g - b) / delta;
    } else if (g == max_val) {
        *h = 2.0f + (b - r) / delta; // 0xc19(%rip) points to 2.0f
    } else {
        *h = 4.0f + (r - g) / delta; // 0xbed(%rip) points to 4.0f
    }

    *h *= 60.0f; // 0xbd8(%rip) points to 60.0f

    if (*h < 0.0f) {
        *h += 360.0f; // 0xbb8(%rip) points to 360.0f
    }
}