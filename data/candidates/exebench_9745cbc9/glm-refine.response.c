int __cdecl itoa(char *str, int i)
{
  char tmp[12]; // Temporary buffer to hold the digits in reverse order
  unsigned int u;
  char *p;
  char *s = str;

  // Determine the absolute value of the integer
  if (i >= 0)
    u = i;
  else
    u = -i;

  // p starts at the end of the temporary buffer and moves backwards
  p = &tmp[11];

  // Extract digits in reverse order
  do
  {
    *p-- = (u % 10) + '0';
    u /= 10;
  } while (u);

  // Prepend the negative sign if the original number was negative.
  // Otherwise, advance p to the first digit written.
  if (i >= 0)
    ++p;
  else
    *p = '-';

  // Copy the generated string from the temporary buffer to the output string.
  // The loop terminates when p reaches the address of 'u', which corresponds
  // to the end of the 'tmp' array (tmp[12]).
  while (p < (char *)&u)
  {
    *s++ = *p++;
  }

  // Null-terminate the string
  *s = '\0';

  // Return the length of the string (pointer difference)
  return (int)(s - str);
}