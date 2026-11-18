int func0(int *numbers, int size)
{
    // Bubble sort the array in ascending order
    for (int outerIndex = 0; outerIndex < size - 1; outerIndex++) {
        for (int innerIndex = 0; innerIndex < size - outerIndex - 1; innerIndex++) {
            // Swap adjacent elements if they are in the wrong order
            if (numbers[innerIndex + 1] < numbers[innerIndex]) {
                int swapTemp = numbers[innerIndex];
                numbers[innerIndex] = numbers[innerIndex + 1];
                numbers[innerIndex + 1] = swapTemp;
            }
        }
    }
    // Initialize minimum difference to the maximum possible integer value
    int minDifference = 0x7fffffff;
    // Find the minimum difference between adjacent elements in the sorted array
    for (int outerIndex = 0; outerIndex < size - 1; outerIndex++) {
        int currentDifference = numbers[outerIndex + 1] - numbers[outerIndex];
        if (currentDifference < minDifference) {
            minDifference = currentDifference;
        }
    }
    return minDifference;
}