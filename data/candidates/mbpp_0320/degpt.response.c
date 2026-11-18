int func0(int n)
{
  int sum_of_squares = 0; // Initialize sum of squares to 0
  int sum_of_numbers = 0;  // Initialize sum of numbers to 0
  for (int current_number = 1; current_number <= n; current_number++) {
    sum_of_squares += current_number * current_number; // Add the square of the current number to sumofsquares
    sum_of_numbers += current_number;        // Add the current number to squareofsum
  }
  return sum_of_numbers * sum_of_numbers - sum_of_squares; // Return the difference between the square of the sum and the sum of the squares
}