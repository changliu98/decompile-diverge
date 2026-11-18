int is_palindrome(int *array, int size)
{
    int i;
    int count = 0;
    for (i = 0; i < size / 2; i++)
    {
        if (array[i] != array[size - 1 - i])
        {
            count++;
        }
    }
    return count;
}