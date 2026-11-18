int func0(int *array, int length)
{
    // Initialize min_val to the maximum possible integer value
    int minimum = 0x7fffffff;
    // Initialize max_val to the minimum possible integer value
    int maximum = -0x80000000;
    // Iterate through each element in the array
    for (int index = 0; index < length; index++) {
        // Update max_val if the current element is greater
        if (maximum < array[index]) {
            maximum = array[index];
        }
        // Update min_val if the current element is smaller
        if (array[index] < minimum) {
            minimum = array[index];
        }
    }
    // Return the difference between the maximum and minimum values
    return maximum - minimum;
}