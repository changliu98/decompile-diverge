void reverse(int *array)
{
    int i;
    int temp;
    for (i = 0; i < 5; i++)
    {
        temp = array[i];
        array[i] = array[10 - i - 1];
        array[10 - i - 1] = temp;
    }
}