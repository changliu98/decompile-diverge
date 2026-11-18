// Function to count pairs with absolute difference equal to k
int countPairsWithDifferenceK(int *numbers, int arraySize, int targetDifference)
{
    int validPairCount = 0; // Initialize pair counter
    for (int firstIndex = 0; firstIndex < arraySize; firstIndex++) { // Iterate through each element
        for (int secondIndex = firstIndex + 1; secondIndex < arraySize; secondIndex++) { // Iterate through subsequent elements
            // Check if absolute difference between arr[i] and arr[j] equals k
            if ((numbers[firstIndex] - numbers[secondIndex] == targetDifference) || (numbers[secondIndex] - numbers[firstIndex] == targetDifference)) {
                validPairCount++; // Increment counter if condition is met
            }
        }
    }
    return validPairCount; // Return total count of valid pairs
}