int func0(int *numbers, int count)
{
    int total = 0; // Initialize sum to 0
    for (int index = 0; index < count; index += 2) { // Iterate through the array with a step of 2
        if (numbers[index] % 2 == 0) { // Check if the current element is even
            total += numbers[index]; // Add the even element to sum
        }
    }
    return total; // Return the sum of even elements at even indices
}