int func0(int *numbers, int count) {
    int index = 0;
    // Iterate through the list until a negative number is found or the end is reached
    while (index < count && numbers[index] >= 0) {
        index++;
    }
    // If all elements are non-negative, return 0
    if (index >= count) {
        return 0;
    }
    // Return the first negative number found
    return numbers[index];
}