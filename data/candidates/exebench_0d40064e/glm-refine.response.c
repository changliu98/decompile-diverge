void __cdecl prtX16(long num, char *str)
{
  char temp[9];
  long numa = num;
  int i;

  // The first byte is initialized to 0, but it is never actually read 
  // because the loops only use indices 1 through 8. It can be safely ignored.
  temp[0] = 0;

  // Convert the number to hex digits in reverse order (least significant nibble first)
  // temp[1] holds the least significant digit, temp[8] holds the most significant.
  for (i = 1; i <= 8; ++i)
  {
    temp[i] = "0123456789abcdef"[numa & 0xF];
    numa >>= 4;
  }

  // Skip leading zeros by moving the index 'i' down to the most significant non-zero digit
  for (i = 8; temp[i] == '0'; --i)
    ;

  // If the entire number was zero, the loop above goes down to i = 0.
  // We force it back to 1 so that we print at least one '0'.
  if (!i)
    i = 1;

  // Copy the significant digits (and the null terminator at temp[0]) to the output string
  while (i >= 0)
  {
    *str++ = temp[i--];
  }
}