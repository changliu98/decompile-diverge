// Function to compute the bitwise XOR of two integer arrays element-wise
// Parameters:
//   test_tup1: Pointer to the first input array
//   test_tup2: Pointer to the second input array
//   res:       Pointer to the output array to store results
//   size:      Number of elements in the arrays
void func0(int *array1, int *array2, int *result, int length)
{
  // Iterate through each element of the arrays
  for (int index = 0; index < length; index++) {
    // Compute the bitwise XOR of corresponding elements and store in result array
    result[index] = array1[index] ^ array2[index];
  }
}