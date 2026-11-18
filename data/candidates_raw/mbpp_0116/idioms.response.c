int to_int(int *array, int size)
{
    int result = 0;
    int i;
    for (i = 0; i < size; i++)
    {
        result = (result * 10) + array[i];
    }
    return result;
}