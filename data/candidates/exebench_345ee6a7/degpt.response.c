int removeElement(int *array, int arraySize, int targetValue) {
    int index = 0;
    while (index < arraySize) {
        if (array[index] == targetValue) {
            // Decrement the effective size of the array
            arraySize--;
            // Replace the current element with the last element in the current range
            array[index] = array[arraySize];
            // Do not increment i, as the new element at nums[i] needs to be checked
        } else {
            // Move to the next element
            index++;
        }
    }
    // Return the new size of the array after removing elements equal to val
    return arraySize;
}