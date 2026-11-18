char * itoa ( long n, char * s, long radix )
{



  char * p = s;
  char * q = s;
  char c;
  long i;
  char digits[37] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";




  if ( !p || radix<2 || radix>36 ) return p;

  if ( radix != 10 && n<0 ) return p;

  if ( n==0 )
  {
    *p++ = '0';
    *p = '\0';
    return p;
  }

  if ( radix == 10 && n<0 )
  {
    *p++ = '-';
    n = 0-n;
  }



  while ( n )
  {
    *p++ = digits[n % radix];
    n /= radix;
  }
  *p = '\0';



  p--;
  while ( q<p )
  {
    c = *q;
    *q = *p;
    *p = c;
    q++;
    p--;
  }
  return s;
}