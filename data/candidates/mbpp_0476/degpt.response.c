int func0(int *array, int length)
{
    // Initialize min_num to the maximum possible integer value
    int minimum_value = 0x7fffffff;
    // Initialize max_num to the minimum possible integer value
    int maximum_value = -0x80000000;
    // Iterate through each element in the array
    for (int index = 0; index < length; index++) {
        // Update max_num if the current element is greater than the current max
        if (maximum_value < array[index]) {
            maximum_value = array[index];
        }
        // Update min_num if the current element is smaller than the current min
        if (array[index] < minimum_value) {
            minimum_value = array[index];
        }
    }
    // Return the sum of the maximum and minimum values found in the array
    return maximum_value + minimum_value;
}