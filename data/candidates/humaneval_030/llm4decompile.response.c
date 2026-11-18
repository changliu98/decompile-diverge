float * func0(float * l, int count, int * out_count)
{
    int i;
    float * arr = malloc(sizeof(float) * count);
    *out_count = 0;
    for (i = 0; i < count; i++)
    {
        if (l[i] > 0)
        {
            arr[(*out_count)++] = l[i];
        }
    }
    return arr;
}