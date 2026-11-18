int func0(int *numbers, int array_size)
{
    int positive_sum = 0; // Initialize sum to zero
    for (int index = 0; index < array_size; index++) { // Iterate through each element in the array
        if (numbers[index] > 0) { // Check if the current element is positive
            positive_sum += numbers[index]; // Add the positive element to the sum
        }
    }
    return positive_sum; // Return the total sum of positive elements
}