int func0(int *numbers, int count)
{
    // Return -1 if the list has fewer than 2 elements
    if (count < 2) {
        return -1;
    }
    // Initialize first and second to maximum integer value
    int min1 = 0x7fffffff;
    int min2 = 0x7fffffff;
    // Iterate through the list to find the two smallest distinct values
    for (int index = 0; index < count; index++) {
        // If current element is smaller than the smallest found so far
        if (numbers[index] < min1) {
            // Update second to be the previous smallest
            min2 = min1;
            // Update first to the current element
            min1 = numbers[index];
        } else if (numbers[index] < min2 && numbers[index] != min1) {
            // If current element is smaller than second and not equal to first
            // Update second to the current element
            min2 = numbers[index];
        }
    }
    // Return second smallest if found, otherwise return -1
    return (min2 == 0x7fffffff) ? -1 : min2;
}