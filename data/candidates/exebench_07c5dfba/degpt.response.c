void _itoa_dec(uint number, char *buffer)
{
  // Iterate 10 times to handle up to 10-digit numbers
  for (uint index = 0; index < 10; index++) {
    // If value is zero and not the first digit, pad with space
    if (number == 0 && index != 0) {
      buffer[9 - index] = ' ';
    } else {
      // Convert current digit to character and store in buffer
      buffer[9 - index] = "0123456789"[number % 10];
    }
    // Remove the last digit from the value
    number /= 10;
  }
}