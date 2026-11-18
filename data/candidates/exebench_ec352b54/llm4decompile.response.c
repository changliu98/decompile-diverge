void swap(float *min, float *max)
{
    if (*min > *max)
    {
        float temp = *max;
        *max = *min;
        *min = temp;
    }
}