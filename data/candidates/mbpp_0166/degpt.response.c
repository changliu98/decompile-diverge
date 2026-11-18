int func0(int *arrayInput, int arraySize)
{
    int evenPairCount = 0; // Initialize counter for even pairs
    for (int indexA = 0; indexA < arraySize; indexA++) { // Iterate through each element
        for (int indexB = indexA + 1; indexB < arraySize; indexB++) { // Iterate through subsequent elements
            if ((arrayInput[indexA] ^ arrayInput[indexB]) % 2 == 0) { // Check if XOR of pair is even
                evenPairCount++; // Increment counter if condition is met
            }
        }
    }
    return evenPairCount; // Return total count of even pairs
}