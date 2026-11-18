void findMinMax(long *numbers, long *minimum, long *maximum)
{
  // Iterate through the array starting from the second element (index 1) up to index 4
  for (int index = 1; index < 5; index++) {
    // Update minimum if current element is smaller than the current minimum
    if (numbers[index] < *minimum) {
      *minimum = numbers[index];
    }
    // Update maximum if current element is larger than the current maximum
    if (*maximum < numbers[index]) {
      *maximum = numbers[index];
    }
  }
}