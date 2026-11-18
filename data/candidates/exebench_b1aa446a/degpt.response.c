char * get_mod_and_div(long *remainder, long *quotient, char *string_buffer, long number)
{
  // Handle negative numbers by adjusting modulo and division results
  if (number < 0) {
    // Calculate negative remainder for negative n
    *remainder = -(number % 10);
    // Calculate negative quotient for negative n
    *quotient = -(number / 10);
    // Set sign character to '-'
    *string_buffer = '-';
    // Return pointer to next position in string buffer
    return string_buffer + 1;
  } else {
    // Calculate positive remainder
    *remainder = number % 10;
    // Calculate positive quotient
    *quotient = number / 10;
    // Return pointer to current position in string buffer
    return string_buffer;
  }
}