int func0(int arraySize, int *numbers)
{
    int index;
    int minFrequency;
    int minimumValue;

    // Initialize minimum value to the first element of the array
    minimumValue = *numbers;
    // Initialize frequency count of the minimum value to 1
    minFrequency = 1;
    // Iterate through the rest of the array starting from the second element
    for (index = 1; index < arraySize; index++) {
        // If current element is smaller than the current minimum, update minimum and reset frequency
        if (numbers[index] < minimumValue) {
            minimumValue = numbers[index];
            minFrequency = 1;
        } 
        // If current element equals the current minimum, increment frequency
        else if (numbers[index] == minimumValue) {
            minFrequency++;
        }
    }
    // Return the frequency of the minimum value in the array
    return minFrequency;
}