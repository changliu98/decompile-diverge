void func0(int input_number, int *counts_array)
{
  int even_digit_count = 0; // Initialize counter for even digits
  int odd_digit_count = 0;  // Initialize counter for odd digits
  int current_number = abs(input_number); // Work with absolute value to handle negative numbers
  do {
    if ((current_number % 10) % 2 == 0) { // Check if the last digit is even
      even_digit_count = even_digit_count + 1;   // Increment even digit count
    }
    else {
      odd_digit_count = odd_digit_count + 1;     // Increment odd digit count
    }
    current_number = current_number / 10;      // Remove the last digit
  } while (0 < current_number);           // Continue until all digits are processed
  *counts_array = even_digit_count;              // Store even count at the first index
  counts_array[1] = odd_digit_count;             // Store odd count at the second index
}