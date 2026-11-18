int func0(int *array, int array_size)
{
  int index;
  // Iterate through the array until the end of the array is reached or a -1 is found
  for (index = 0; (index < array_size && (array[index] != -1)); index = index + 1) {
  }
  // Return the index of the first -1, or the size if no -1 is found
  return index;
}