int func0(int *digits, int num_digits)
{
  int number = 0; // Initialize result to 0
  for (int index = 0; index < num_digits; index++) { // Iterate through the list
    number = number * 10 + digits[index]; // Accumulate digits to form a number
  }
  return number; // Return the computed number
}