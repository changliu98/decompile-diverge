int func0(int size, int *array)
{
    int index;
    int frequency;
    int max_value;

    // Initialize minimum value to the first element of the array
    max_value = *array;
    // Initialize frequency count of the minimum value to 1
    frequency = 1;
    // Iterate through the array starting from the second element
    for (index = 1; index < size; index++) {
        // If current element is greater than the current minimum, update minimum and reset frequency
        if (max_value < array[index]) {
            max_value = array[index];
            frequency = 1;
        } 
        // If current element equals the current minimum, increment frequency
        else if (array[index] == max_value) {
            frequency++;
        }
    }
    // Return the frequency of the maximum value in the array
    return frequency;
}