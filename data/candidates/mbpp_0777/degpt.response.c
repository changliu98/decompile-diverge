int func0(int *numbers, int count)
{
    // Sort the array in ascending order using qsort
    qsort(numbers, (long)count, 4, compareFunction);
    
    // Initialize sum with the first element of the sorted array
    int uniqueSum = *numbers;
    
    // Iterate through the array to sum unique elements
    for (int index = 0; index < count - 1; index++) {
        // If the current element is different from the next, add the next element to sum
        if (numbers[index] != numbers[index + 1]) {
            uniqueSum = numbers[index + 1] + uniqueSum;
        }
    }
    
    // Return the calculated sum of unique elements
    return uniqueSum;
}