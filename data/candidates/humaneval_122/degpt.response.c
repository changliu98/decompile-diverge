int func0(int *numbers, int count)
{
    int total = 0; // Initialize sum to zero
    for (int index = 0; index < count; index++) { // Iterate through the first k elements of the array
        if (numbers[index] > -100 && numbers[index] < 100) { // Check if the current element is within the range (-100, 100)
            total += numbers[index]; // Add the current element to the sum if it is within the range
        }
    }
    return total; // Return the calculated sum
}