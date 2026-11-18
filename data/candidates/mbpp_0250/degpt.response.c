// Function to count occurrences of a specific value in an integer array
// Parameters:
//   arr      - Pointer to the integer array
//   arr_size - Number of elements in the array
//   x        - The value to search for in the array
// Returns:
//   The number of times x appears in the array
int func0(int *numbers, int num_elements, int target_value)
{
    int occurrence_count = 0; // Initialize counter for occurrences of x
    for (int index = 0; index < num_elements; index++) { // Iterate through each element in the array
        if (numbers[index] == target_value) { // Check if current element matches x
            occurrence_count++; // Increment counter if match is found
        }
    }
    return occurrence_count; // Return total count of occurrences
}