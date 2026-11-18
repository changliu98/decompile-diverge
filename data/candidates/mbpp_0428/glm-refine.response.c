void __cdecl shell_sort(int *arr, int length)
{
    int gap, i, j;
    int current_item;

    // Start with a large gap, then reduce the gap
    for (gap = length / 2; gap > 0; gap /= 2)
    {
        // Perform a gapped insertion sort for this gap size
        for (i = gap; i < length; ++i)
        {
            current_item = arr[i];

            // Shift earlier gap-sorted elements up until the correct 
            // location for current_item is found
            for (j = i; j >= gap && arr[j - gap] > current_item; j -= gap)
            {
                arr[j] = arr[j - gap];
            }

            // Put current_item in its correct location
            arr[j] = current_item;
        }
    }
}