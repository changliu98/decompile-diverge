void __cdecl itoa(char *buf, int base, long d)
{
  char v3; // al
  char v4; // cl
  char *v5; // rax
  char tmp; // [rsp+1h] [rbp-41h]
  int remainder; // [rsp+2h] [rbp-40h]
  int divisor; // [rsp+6h] [rbp-3Ch]
  unsigned __int64 ud; // [rsp+Ah] [rbp-38h]
  char *p2; // [rsp+12h] [rbp-30h]
  char *p1; // [rsp+1Ah] [rbp-28h]
  char *p; // [rsp+22h] [rbp-20h]
  char *bufa; // [rsp+3Ah] [rbp-8h]

  bufa = buf;
  p = buf;
  ud = d;
  divisor = 10;
  if ( base == 100 && d < 0 )
  {
    p = buf + 1;
    *buf = 45;
    bufa = buf + 1;
    ud = -d;
  }
  else if ( base == 120 )
  {
    divisor = 16;
  }
  do
  {
    remainder = ud % divisor;
    v3 = 87;
    if ( remainder < 10 )
      v3 = 48;
    v4 = remainder + v3;
    v5 = p++;
    *v5 = v4;
    ud /= (unsigned __int64)divisor;
  }
  while ( ud );
  *p = 0;
  p1 = bufa;
  for ( p2 = p - 1; p1 < p2; --p2 )
  {
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
    ++p1;
  }
}