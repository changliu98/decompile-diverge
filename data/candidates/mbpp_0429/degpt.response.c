// Performs bitwise AND operation on two integer arrays and stores the result in a third array.
// Parameters:
//   test_tup1: Pointer to the first input array.
//   test_tup2: Pointer to the second input array.
//   res:       Pointer to the output array where results are stored.
//   size:      Number of elements in the arrays.
void func0(int *array1, int *array2, int *result, int length)
{
  // Iterate through each element of the arrays up to the specified size.
  for (int index = 0; index < length; index++) {
    // Perform bitwise AND between corresponding elements of test_tup1 and test_tup2,
    // and store the result in the corresponding position of the res array.
    result[index] = array1[index] & array2[index];
  }
}