int is_sorted(float *numbers, int size, float threshold)
{
    int i; int j;
    for (i = 0; i < size; i++)
        for (j = i + 1; j < size; j++)
            if (numbers[i] - numbers[j] < threshold)
                return 1;
    return 0;
}