void __cdecl itoa(unsigned int value, char *buffer)
{
  int idx;        // Tracks the current index in the buffer
  int remainder;  // Holds the remainder (current digit)

  // Initialize the end of the 8-byte buffer with a null terminator
  idx = 7;
  buffer[7] = '\0';

  // Convert digits from least significant to most significant
  do
  {
    // Decrement idx and store the character representation of the digit
    remainder = idx--;
    buffer[remainder] = (value % 10) + '0'; 
    
    // Shift the value down by one decimal place
    value /= 10;
  }
  while (value); // Continue until all digits are processed
}