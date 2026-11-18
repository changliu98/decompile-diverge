int __cdecl LI_ltostr(char *buf, long val)
{
  int len = 1;
  char *start = buf;

  // Handle negative numbers
  if (val < 0)
  {
    len = 2; // 1 for the '-' sign, 1 for the first digit
    *buf = '-';
    start = buf + 1;
    val = -val;
  }

  char *end = start;

  // Write digits in reverse order
  while (val > 9)
  {
    *end++ = (val % 10) + '0';
    val /= 10;
  }
  *end = val + '0';
  end[1] = '\0'; // Null-terminate the string

  // Calculate the total length of the resulting string
  int total_len = (end - start) + len;

  // Reverse the digits in place to correct the order
  while (start < end)
  {
    char swap = *end;
    *end-- = *start;
    *start++ = swap;
  }

  return total_len;
}