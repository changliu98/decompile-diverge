// Copies the first three elements from array 'a' to array 'b'
void cpy3(double *source_array, double *destination_array)
{
  *destination_array = *source_array;      // Copy the first element
  destination_array[1] = source_array[1];  // Copy the second element
  destination_array[2] = source_array[2];  // Copy the third element
}