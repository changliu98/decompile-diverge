int __cdecl ltos(char *s, long num)
{
  char buf[20];
  char *p = buf;
  char *sa = s;

  // Handle negative numbers by taking the absolute value.
  // Note: The original code uses signed negation, which leaves
  // LONG_MIN unchanged, preserving its original UB/edge-case behavior.
  unsigned long anum = num >= 0 ? num : -num;

  // Generate digits in reverse order
  for (; anum > 9; anum /= 10)
  {
    *p++ = (char)(anum % 10 + '0');
  }

  // Add the negative sign if the original number was negative
  if (num < 0)
  {
    *sa++ = '-';
  }

  // Append the most significant digit (which is <= 9)
  *sa++ = (char)(anum + '0');

  // Reverse the generated digits and append them to the string
  while (p > buf)
  {
    *sa++ = *--p;
  }

  // Null-terminate the string
  *sa = '\0';
  
  return 0;
}