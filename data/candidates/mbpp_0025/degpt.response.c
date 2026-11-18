int func0(int *numbers, int count)
{
    int index, comparisonIndex, currentValue;
    // Insertion sort to sort the array in ascending order
    for (index = 1; index < count; index++) {
        currentValue = numbers[index];
        comparisonIndex = index - 1;
        // Shift elements greater than temp one position ahead
        while (comparisonIndex >= 0 && numbers[comparisonIndex] > currentValue) {
            numbers[comparisonIndex + 1] = numbers[comparisonIndex];
            comparisonIndex--;
        }
        // Place temp in its correct position
        numbers[comparisonIndex + 1] = currentValue;
    }
    // Calculate the product of unique elements in the sorted array
    int uniqueProduct = 1;
    for (index = 0; index < count; index++) {
        // Multiply only if it's the first element or different from the previous one
        if (index == 0 || numbers[index - 1] != numbers[index]) {
            uniqueProduct *= numbers[index];
        }
    }
    return uniqueProduct;
}