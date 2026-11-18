/**
 * @brief Calculates the sum of all elements in the array that appear more than once.
 * 
 * This function iterates through the array and for each element, counts its total
 * occurrences. If an element occurs more than once, it is added to the running sum.
 * Note: If an element appears k times (where k > 1), each of its k occurrences 
 * will be added to the final sum. Unique elements are ignored.
 * 
 * @param arr Pointer to the array of integers.
 * @param n   Number of elements in the array.
 * @return    The accumulated sum of all duplicate elements.
 */
int __cdecl sum_duplicate_elements(int *arr, int n)
{
    int i, j, count, sum;

    sum = 0;
    for (i = 0; i < n; ++i)
    {
        count = 1; // Start at 1 to include the current element arr[i]
        
        // Count occurrences of arr[i] in the entire array
        for (j = 0; j < n; ++j)
        {
            if (arr[j] == arr[i] && j != i)
            {
                ++count;
            }
        }
        
        // If the element is a duplicate, add it to the sum
        if (count > 1)
        {
            sum += arr[i];
        }
    }
    
    return sum;
}