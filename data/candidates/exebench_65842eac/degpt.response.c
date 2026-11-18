void minmax(int *current_value, int *array_length, int *minimum_value, int *maximum_value)
{
  // Update max if current element is greater than current max
  if (*maximum_value < *current_value) {
    *maximum_value = *current_value;
  }
  // Update min if current element is smaller than current min
  if (*current_value < *minimum_value) {
    *minimum_value = *current_value;
  }
}