bool __cdecl func0(const int *arr, int size) 
{
    // Allocate a Variable Length Array (VLA) on the stack to track seen elements.
    // The original assembly used a manual stack pointer manipulation to allocate this.
    int seen[size];
    int temp_size = 0;

    for (int i = 0; i < size; ++i) 
    {
        int ele = arr[i];
        bool found = false;

        // Check if the current element has already been seen
        for (int j = 0; j < temp_size; ++j) 
        {
            if (seen[j] == ele) 
            {
                found = true;
                break;
            }
        }

        // If a duplicate is found, the array does not contain all unique elements
        if (found) 
            return false;

        // Add the new unique element to the seen list
        seen[temp_size++] = ele;
    }

    return true;
}