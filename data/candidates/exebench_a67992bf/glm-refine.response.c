size_t __cdecl itoa(char *str, int i)
{
  char tmp[12];          // Temporary buffer to hold the digits in reverse order
  unsigned int u;        // Unsigned representation of the absolute value
  char *p = &tmp[11];    // Pointer to the end of the temporary buffer
  char *s = str;         // Working pointer to the output string

  // Convert negative integers to their positive unsigned equivalent
  if (i >= 0)
    u = i;
  else
    u = -i;

  // Generate digits in reverse order
  do
  {
    *p-- = (u % 10) + '0';
    u /= 10;
  }
  while (u);

  // Prepend the negative sign if the original number was negative.
  // Otherwise, advance the pointer to the first digit generated.
  if (i >= 0)
    ++p;
  else
    *p = '-';

  // Copy the generated characters to the output string.
  // The loop terminates when `p` reaches the address of `u` (which is 
  // located exactly at the end of the `tmp` array boundary in memory).
  while (p < (char *)&u)
  {
    *s++ = *p++;
  }

  // Null-terminate the string
  *s = '\0';

  // Return the length of the string
  return s - str;
}