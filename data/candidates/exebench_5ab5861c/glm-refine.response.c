char *__cdecl itoa(long n, char *str, long radix)
{
  char temp;
  char *head;
  char *p;
  char digit[37];
  
  memcpy(digit, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ", sizeof(digit));
  
  // Validate input arguments
  if ( !str || radix < 2 || radix > 36 )
    return str;
  if ( radix != 10 && n < 0 )
    return str;

  // Handle zero as a special case
  if ( !n )
  {
    *str = '0';
    str[1] = '\0';
    return str + 1;
  }

  p = str;
  head = str;

  // Handle negative decimal numbers
  if ( radix == 10 && n < 0 )
  {
    p = str + 1;
    *str = '-';
    n = -n;
  }

  // Convert number to string (in reverse order)
  while ( n )
  {
    *p++ = digit[n % radix];
    n /= radix;
  }
  *p = '\0';

  // Reverse the string in-place
  for ( char *pa = p - 1; head < pa; --pa )
  {
    temp = *head;
    *head = *pa;
    *pa = temp;
    ++head;
  }

  return str;
}