float func0(float a, float b, float c) {
    float max;
    if (b > a)
        max = b;
    else if (a > c)
        max = c;
    else
        max = a;
    return max;
}