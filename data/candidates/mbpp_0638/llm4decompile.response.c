int func0(int v, int t)
{
    double windchill = 35.74 + 0.6215 * t + (0.4275 * t - 35.75) * pow(v, 0.16);
    return (int)round(windchill);
}