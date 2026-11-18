// Function to find the maximum value in an array of floats
// Parameters:
//   l     - pointer to the array of floats
//   size  - number of elements in the array
// Returns:
//   The maximum value found in the array
float func0(float *array, int array_size)
{
    // Initialize max with a default value from global variable DAT_00102004
    float max_value = DAT_00102004;
    
    // Iterate through each element in the array
    for (int index = 0; index < array_size; index++) {
        // If current element is greater than max, update max
        if (max_value < array[index]) {
            max_value = array[index];
        }
    }
    
    // Return the maximum value found
    return max_value;
}