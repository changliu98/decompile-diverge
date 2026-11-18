int binary_search(int *array, int n, int value)
{
    int left = 0;
    int right = n - 1;

    while (left <= right)
    {
        int middle = left + ((right - left) >> 1);

        if (array[middle] == value)
        {
            return middle;
        }
        else if (array[middle] < value)
        {
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
    }

    return -1;
}