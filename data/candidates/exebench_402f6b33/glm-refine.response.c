void __cdecl itoa(int num, char *str, int base)
{
  char tmp[16];
  int i = 0;
  int sign = num;
  
  // Handle negative numbers
  if (num < 0)
    num = -num;

  // Convert the number to digits in reverse order
  if (num != 0)
  {
    while (num != 0)
    {
      tmp[i++] = digits[num % base];
      num /= base;
    }
  }
  else
  {
    tmp[i++] = '0';
  }

  // Append the minus sign if the original number was negative
  if (sign < 0)
    tmp[i++] = '-';

  // Reverse the digits and write them to the output string
  while (i > 0)
  {
    *str++ = tmp[--i];
  }
  
  // Null-terminate the string
  *str = '\0';
}