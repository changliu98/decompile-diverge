float LerpAngle(float a, float b, float t) {
    float result;

    if (b - a > 180.0f) {
        b -= 360.0f;
    }

    if (a - b > 180.0f) {
        b += 360.0f;
    }

    result = a + (b - a) * t;

    return result;
}