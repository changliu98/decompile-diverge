// Function to count the number of pairs in the array that sum up to a given value
int func0(int *numbers, int size, int targetSum)
{
    int pairCount = 0; // Initialize counter for valid pairs
    for (int firstIndex = 0; firstIndex < size; firstIndex++) { // Iterate through each element of the array
        for (int secondIndex = firstIndex + 1; secondIndex < size; secondIndex++) { // Iterate through subsequent elements to form pairs
            if (numbers[firstIndex] + numbers[secondIndex] == targetSum) { // Check if the sum of the pair equals the target sum
                pairCount++; // Increment the counter if the condition is met
            }
        }
    }
    return pairCount; // Return the total count of valid pairs
}