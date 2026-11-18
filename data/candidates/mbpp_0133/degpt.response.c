int func0(int *numbers, int array_size)
{
    int negative_sum = 0; // Initialize sum to zero
    for (int index = 0; index < array_size; index++) { // Iterate through each element in the array
        if (numbers[index] < 0) { // Check if the current element is negative
            negative_sum += numbers[index]; // Add the negative element to the sum
        }
    }
    return negative_sum; // Return the sum of all negative elements
}