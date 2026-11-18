// Wrapper function to find a peak element in the array
// Parameters:
//   arr - pointer to the input array
//   n   - number of elements in the array
// Returns:
//   The value of a peak element found using the utility function
int find_peak(int *array, int size)
{
    // Call the utility function to find a peak in the entire array
    return find_peak_util(array, 0, size - 1, size);
}