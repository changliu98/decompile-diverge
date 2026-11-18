static float cmp_float_asc(const void *a, const void *b)
{
    float x = *(float *)a;
    float y = *(float *)b;

    return ((x) - (y));
}