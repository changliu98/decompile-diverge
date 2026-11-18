int max(int *list, int size)
{
    int *freq = (int *)calloc(size + 1, sizeof(int));
    int max = -1;
    int i = 0;
    for (i = 0; i < size; i++)
    {
        freq[list[i]]++;
        if (freq[list[i]] >= list[i] && list[i] > max)
            max = list[i];
    }
    free(freq);
    return max;
}