int func0(int *numbers, int array_size)
{
    int index = 0;
    // Iterate through the array to find the first even number
    while (index < array_size && numbers[index] % 2 != 0) {
        index++;
    }
    // If no even number is found, return -1
    if (index >= array_size) {
        return -1;
    }
    // Return the first even number found
    return numbers[index];
}