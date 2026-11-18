float clamp(float v, float max, float min) {
    float result;

    if (max > v) {
        result = max;
    } else if (v > min) {
        result = min;
    } else {
        result = v;
    }

    return result;
}