// Assuming itoa_dec_dectab is defined elsewhere as:
// const char itoa_dec_dectab[] = "0123456789";

#define BUFFER_SIZE 10
#define BASE 10

void __cdecl itoa_dec(unsigned int val, char *buf)
{
  unsigned int i;

  // Process 10 digits, filling the buffer from right to left
  for (i = 0; i < BUFFER_SIZE; ++i)
  {
    if (val == 0 && i > 0)
    {
      // If the value is exhausted, pad the remaining leading spaces
      buf[BUFFER_SIZE - 1 - i] = ' ';
    }
    else
    {
      // Extract the least significant digit and convert it to a character
      buf[BUFFER_SIZE - 1 - i] = itoa_dec_dectab[val % BASE];
    }
    
    // Shift down to the next digit
    val /= BASE;
  }
}