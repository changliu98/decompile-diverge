int binary_search(int *array, int n, int x)
{
    int low = 0;
    int high = n;
    int mid = (low + high) / 2;
    while (low < high)
    {
        mid = (low + high) / 2;
        if (array[mid] < x)
        {
            low = mid + 1;
        }
        else
        {
            high = mid;
        }
    }
    return low;
}