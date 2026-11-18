int func0(int *numbers, int count)
{
  int index;
  int minimum;
  
  // Initialize max with the first element of the list
  minimum = *numbers;
  // Iterate through the list to find the minimum value
  for (index = 0; index < count; index = index + 1) {
    // Update max if the current element is smaller than the current max
    if (numbers[index] < minimum) {
      minimum = numbers[index];
    }
  }
  // Return the minimum value found in the list
  return minimum;
}