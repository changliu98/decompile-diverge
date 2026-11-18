float func0(float a, float b, float c)
{
    float s, area;

    if (a + b > c && a + c > b && b + c > a)
    {
        s = (a + b + c) / 2;
        area = sqrtf(s * (s - a) * (s - b) * (s - c));
        area = roundf(area * 1000000.0f) / 1000000.0f;
        return area;
    }
    else
    {
        return -1.0f;
    }
}