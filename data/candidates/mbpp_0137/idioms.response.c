double func0(int *array, int n)
{
    int i;
    int success = 0;
    for (i = 0; i < n; i++) {
        if (array[i] == 0)
            success++;
    }
    return round((double)success / n * 100) / 100;
}