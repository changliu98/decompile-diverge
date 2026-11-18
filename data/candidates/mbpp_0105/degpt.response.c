// Function to calculate the sum of all elements in an integer array
int func0(int *numbers, int length)
{
    int sum = 0; // Initialize sum accumulator to zero
    for (int index = 0; index < length; index++) { // Iterate through each element of the array
        sum += numbers[index]; // Add current element to the total sum
    }
    return sum; // Return the calculated sum
}