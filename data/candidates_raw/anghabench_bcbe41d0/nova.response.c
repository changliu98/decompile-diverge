float func0(float a, float b, float c) {
    float max;
    if (a > c)
        max = a;
    else if (b > c)
        max = b;
    else
        max = c;
    return max;
}