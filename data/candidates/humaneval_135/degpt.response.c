int func0(int *numbers, int count)
{
    int lastDecreaseIndex = -1; // Initialize max to -1, assuming no valid index found yet
    for (int currentIndex = 1; currentIndex < count; currentIndex++) {
        if (numbers[currentIndex] < numbers[currentIndex - 1]) { // Check if current element is less than the previous one
            lastDecreaseIndex = currentIndex; // Update max to the current index
        }
    }
    return lastDecreaseIndex; // Return the last index where arr[i] < arr[i-1], or -1 if no such index exists
}