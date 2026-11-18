// Sorts the input array 'arr' of size 'n' in ascending order using qsort,
// then copies the sorted elements into the 'result' array.
void func0(int *input_array, int array_size, int *output_array)
{
  // Sort the array using the comparison function cmpfunc
  qsort(input_array, (long)array_size, 4, cmpfunc);
  
  // Copy the sorted elements from 'arr' to 'result'
  for (int index = 0; index < array_size; index++) {
    output_array[index] = input_array[index];
  }
}