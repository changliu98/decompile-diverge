// Copies the first three elements from double array v1 to float array v2
// Performs explicit type casting from double to float for each element
// Returns 0 to indicate successful completion
int matCopyVdf(double *source_array, float *dest_array)
{
  // Copy first element with type conversion
  *dest_array = (float)*source_array;
  // Copy second element with type conversion
  dest_array[1] = (float)source_array[1];
  // Copy third element with type conversion
  dest_array[2] = (float)source_array[2];
  // Return success status
  return 0;
}