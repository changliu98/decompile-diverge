float func0(float a, float b, float c) {
    float s, area;

    if (a >= (b + c) || b >= (a + c) || c >= (a + b))
        area = INVALID;
    else {
        s = (a + b + c) / 2;
        area = sqrt(s * (s - a) * (s - b) * (s - c));
        area /= PRECISION;
    }

    return area;
}