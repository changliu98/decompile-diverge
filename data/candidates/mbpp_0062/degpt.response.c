int func0(int *array, int length)
{
  int index;
  int minimum_value = 0x7fffffff; // Initialize min_val to the maximum possible integer value
  for (index = 0; index < length; index++) {
    if (array[index] < minimum_value) {
      minimum_value = array[index]; // Update min_val if the current element is smaller
    }
  }
  return minimum_value; // Return the minimum value found in the array
}