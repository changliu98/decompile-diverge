void shift(int *array, int size, int *new_array)
{
    new_array[0] = array[size - 1];
    for (int i = 1; i < size + 1; i++)
    {
        new_array[i] = array[i - 1];
    }
}