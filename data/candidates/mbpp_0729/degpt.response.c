void func0(int *first_array, int *second_array, int *sum_array, int array_length)
{
    // Iterate through each element of the arrays up to the specified size
    for (int index = 0; index < array_length; index++) {
        // Add corresponding elements from nums1 and nums2, and store the result in result array
        sum_array[index] = first_array[index] + second_array[index];
    }
}