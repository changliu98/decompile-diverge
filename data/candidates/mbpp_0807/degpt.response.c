int func0(int *numbers, int array_size)
{
  int index = 0;
  // Find the first odd number in the array
  while (index < array_size && numbers[index] % 2 == 0) {
    index++;
  }
  // If no odd number is found, return -1
  if (index == array_size) {
    return -1;
  }
  // Return the first odd number found
  return numbers[index];
}