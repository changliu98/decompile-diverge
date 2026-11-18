char *__cdecl itoa(int n, char *str, int radix)
{
  char temp;
  char *head;
  char *p;
  char digit[37];
  
  memcpy(digit, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ", sizeof(digit));
  
  if ( !str || radix < 2 || radix > 36 )
    return str;
    
  if ( radix != 10 && n < 0 )
    return str;
    
  p = str;
  head = str;
  
  if ( n == 0 )
  {
    *str = '0';
    str[1] = '\0';
    return str + 1;
  }

  if ( radix == 10 && n < 0 )
  {
    *str = '-';
    p = str + 1;
    n = -n;
  }
  
  while ( n )
  {
    *p++ = digit[n % radix];
    n /= radix;
  }
  *p = '\0';
  
  // Reverse the generated string
  for ( char *pa = p - 1; head < pa; --pa )
  {
    temp = *head;
    *head = *pa;
    *pa = temp;
    ++head;
  }
  
  return str;
}