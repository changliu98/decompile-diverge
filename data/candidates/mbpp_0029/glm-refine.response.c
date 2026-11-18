int find_first_odd_occurrence(int *arr, int arr_size)
{
    for (int i = 0; i < arr_size; ++i)
    {
        int current = arr[i];
        int count = 0;
        
        for (int j = 0; j < arr_size; ++j)
        {
            if (current == arr[j])
                ++count;
        }
        
        if (count % 2)
            return current;
    }
    return -1;
}