int *get_max_array(int *array, int size)
{
    int *max_array = ((void *)0);
    int i = 0;
    int max = 0;
    if (size <= 0)
        return ((void *)0);
    max_array = (int *)malloc(sizeof(int)*size);
    if (max_array == ((void *)0))
        return ((void *)0);
    max = array[0];
    for (i = 0; i < size; i++)
    {
        if (array[i] > max)
            max = array[i];
        max_array[i] = max;
    }
    return max_array;
}