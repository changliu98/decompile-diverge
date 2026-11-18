void __cdecl arraylist_sort_internal(
        ArrayListValue *list_data,
        unsigned int list_length,
        ArrayListCompareFunc compare_func)
{
    // Base case: arrays of length 0 or 1 are already sorted
    if (list_length > 1)
    {
        // Choose the last element as the pivot
        ArrayListValue pivot = list_data[list_length - 1];
        
        // 'partition_index' divides elements less than pivot from elements greater than pivot
        unsigned int partition_index = 0; 

        for (unsigned int i = 0; i < list_length - 1; ++i)
        {
            // If the current element is smaller than the pivot, swap it to the left side
            if (compare_func(list_data[i], pivot) < 0)
            {
                ArrayListValue tmp = list_data[i];
                list_data[i] = list_data[partition_index];
                list_data[partition_index] = tmp;
                ++partition_index;
            }
        }

        // Move the pivot to its final sorted position
        list_data[list_length - 1] = list_data[partition_index];
        list_data[partition_index] = pivot;

        // Recursively sort the left partition (elements less than pivot)
        arraylist_sort_internal(list_data, partition_index, compare_func);

        // Recursively sort the right partition (elements greater than pivot)
        arraylist_sort_internal(&list_data[partition_index + 1], list_length - partition_index - 1, compare_func);
    }
}