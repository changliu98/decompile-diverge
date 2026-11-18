int func0(int *array, size_t length)
{
    int index = 0;
    // Skip elements that are less than or equal to -1
    while (index < length && array[index] <= -1) {
        index++;
    }
    // If all elements were <= -1, return -1
    if (index == length) {
        return -1;
    }
    // Return the first element that is greater than -1
    return array[index];
}