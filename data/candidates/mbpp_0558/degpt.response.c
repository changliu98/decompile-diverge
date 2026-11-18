// Function to calculate the sum of digits of the absolute difference between two integers
int func0(int first_number, int second_number)
{
  // Calculate the absolute difference between n1 and n2
  int absolute_difference = abs(first_number - second_number);
  // Initialize sum to 0
  int digit_sum = 0;
  // Loop through each digit of distance from right to left
  for (; 0 < absolute_difference; absolute_difference = absolute_difference / 10) {
    // Add the last digit of distance to sum
    digit_sum = absolute_difference % 10 + digit_sum;
  }
  // Return the sum of digits
  return digit_sum;
}