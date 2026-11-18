bool func0(float a, float b, float c) {
    float d1 = a * a + b * b - c * c;
    float d2 = a * a + c * c - b * b;
    float d3 = b * b + c * c - a * a;

    if (fabs(d1) <= 1e-4 || fabs(d2) <= 1e-4 || fabs(d3) <= 1e-4) {
        return true;
    }
    return false;
}