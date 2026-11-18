void clamp(int *a, int *b, int max)
{
    *b += *a / max;
    *a %= max;
}