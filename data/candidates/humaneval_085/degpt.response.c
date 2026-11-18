int func0(int *numbers, int length)
{
  int total = 0;
  // Iterate through odd-indexed elements (1, 3, 5, ...) of the array
  // The loop condition i * 2 + 1 < size ensures we stay within bounds
  for (int index = 0; index * 2 + 1 < length; index++) {
    // Check if the current odd-indexed element is even
    if (numbers[index * 2 + 1] % 2 == 0) {
      // Add the even-valued odd-indexed element to the sum
      total += numbers[index * 2 + 1];
    }
  }
  // Return the sum of all even numbers located at odd indices
  return total;
}