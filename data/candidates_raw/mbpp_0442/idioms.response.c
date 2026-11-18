static double get_percent(int *array, int n)
{
    int i; int count = 0;
    for (i = 0; i < n; i++)
        if (array[i] > 0)
            count++;
    return round((count * 1.0 / n * 100)) / 100.0;
}