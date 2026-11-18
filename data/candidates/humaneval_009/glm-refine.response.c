int *func0(const int *numbers, int size)
{
    if (size <= 0)
        return NULL;

    int *running_max = (int *)malloc(sizeof(int) * size);
    if (!running_max)
        return NULL;

    int current_max = numbers[0];
    for (int i = 0; i < size; ++i)
    {
        if (numbers[i] > current_max)
            current_max = numbers[i];
        
        running_max[i] = current_max;
    }

    return running_max;
}