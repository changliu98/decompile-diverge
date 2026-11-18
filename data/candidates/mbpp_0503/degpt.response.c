void func0(int *inputArray, int arrayLength, int *outputArray)
{
  // Iterate through the array up to the second-to-last element
  for (int index = 0; index < arrayLength - 1; index++) {
    // Store the sum of adjacent elements in the result array
    outputArray[index] = inputArray[index] + inputArray[index + 1];
  }
}