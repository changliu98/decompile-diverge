void swap(float *a, float *b)
{
    if(*a > *b)
    {
        float temp = *b;
        *b = *a;
        *a = temp;
    }
}