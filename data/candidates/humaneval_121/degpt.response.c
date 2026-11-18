int func0(int *numbers, int length)
{
    int total = 0;
    // Iterate through the array, processing every other element starting from index 0
    // The condition i * 2 < size ensures we don't access out of bounds
    for (int index = 0; index * 2 < length; index++) {
        // Access the element at index 2*i (equivalent to lst[i << 1])
        // Check if the element is odd
        if (numbers[index << 1] % 2 == 1) {
            // Add the odd element to the sum
            total += numbers[index << 1];
        }
    }
    // Return the sum of all odd elements at even indices
    return total;
}