// Function to calculate the sum of all elements in the integer array 'dict'
// Parameters:
//   dict  - pointer to the first element of the integer array
//   size  - number of elements in the array
// Returns:
//   The sum of all elements in the array
int func0(int *numbers, int length)
{
    int total = 0; // Initialize sum to zero
    for (int index = 0; index < length; index++) { // Iterate through each element in the array
        total += numbers[index]; // Add the current element to the sum
    }
    return total; // Return the calculated sum
}