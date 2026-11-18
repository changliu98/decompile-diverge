// Finds the maximum value in a 1D double array and stores the result
// Parameters:
//   input   - Pointer to the input array of doubles
//   len     - Length of the input array
//   retVals - Output array where retVals[0] is the index of max value and retVals[1] is the max value itself
void max1D_double(double *data, int size, double *result)
{
  int index;
  // Initialize maxVal with a default constant value
  double maximum_value = DAT_00102008;
  // Initialize maxIdx with a default constant value cast to int
  int maximum_index = (int)DAT_00102010;

  // Iterate through the input array to find the maximum value
  for (index = 0; index < size; index++) {
    // Update maxVal and maxIdx if current element is greater than or equal to maxVal
    // and not equal to maxVal (to handle potential floating-point equality issues)
    if (maximum_value <= data[index] && data[index] != maximum_value) {
      maximum_value = data[index];
      maximum_index = index;
    }
  }
  // Store the maximum value at index 1 of the output array
  result[1] = maximum_value;
  // Store the index of the maximum value at index 0 of the output array (cast to double)
  *result = (double)maximum_index;
}