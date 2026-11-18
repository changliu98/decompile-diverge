// Function to find the maximum value in an array of doubles
// Parameters:
//   sigIn: Pointer to the input array
//   sigInLength: Length of the input array
//   sigMax: Pointer to store the maximum value found
void swt_max(double *inputArray, int arrayLength, double *maxValue)
{
  // Initialize the maximum value with the first element of the array
  *maxValue = *inputArray;
  
  // Iterate through the rest of the array starting from the second element
  for (int index = 1; index < arrayLength; index++) {
    // If the current element is greater than the current maximum, update the maximum
    if (inputArray[index] > *maxValue) {
      *maxValue = inputArray[index];
    }
  }
}