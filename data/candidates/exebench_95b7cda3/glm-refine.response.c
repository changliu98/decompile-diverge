void __cdecl itoa(char *buf, int base, long d)
{
  char tmp;
  int remainder;
  int divisor;
  uint64_t ud;
  char *p2;
  char *p1;
  char *p;

  p = buf;
  ud = d;
  divisor = 10;
  
  // Base 100 is used as a flag for signed decimal formatting
  if ( base == 100 && d < 0 )
  {
    *buf = '-';          // 45
    p = buf + 1;
    ud = -d;
  }
  else if ( base == 120 ) // 'x'
  {
    divisor = 16;
  }

  // Convert number to string in reverse order
  do
  {
    remainder = ud % divisor;
    
    // If remainder >= 10, use 'W' (87) as the base for alpha hex digits
    // Otherwise, use '0' (48) as the base for numeric digits
    char offset = (remainder < 10) ? '0' : 'W';
    
    *p++ = remainder + offset;
    ud /= (unsigned __int64)divisor;
  }
  while ( ud );
  
  *p = '\0';

  // Reverse the generated string in-place
  // p1 starts at the beginning of the written digits (skipping '-' if present)
  p1 = (base == 100 && d < 0) ? buf + 1 : buf;
  for ( p2 = p - 1; p1 < p2; --p2 )
  {
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
    ++p1;
  }
}