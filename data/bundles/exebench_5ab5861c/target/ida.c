char *__cdecl itoa(long n, char *str, long radix)
{
  char *v3; // rax
  char temp; // [rsp+Fh] [rbp-61h]
  char *head; // [rsp+10h] [rbp-60h]
  char *p; // [rsp+18h] [rbp-58h]
  char *pb; // [rsp+18h] [rbp-58h]
  char *pa; // [rsp+18h] [rbp-58h]
  char digit[37]; // [rsp+20h] [rbp-50h] BYREF
  long radixa; // [rsp+50h] [rbp-20h]
  char *stra; // [rsp+58h] [rbp-18h]
  long na; // [rsp+60h] [rbp-10h]

  na = n;
  stra = str;
  radixa = radix;
  memcpy(digit, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ", sizeof(digit));
  p = stra;
  head = stra;
  if ( !stra || radixa < 2 || radixa > 36 )
    return stra;
  if ( radixa != 10 && na < 0 )
    return stra;
  if ( na )
  {
    if ( radixa == 10 && na < 0 )
    {
      p = stra + 1;
      *stra = 45;
      na = -na;
    }
    while ( na )
    {
      v3 = p++;
      *v3 = digit[na % radixa];
      na /= radixa;
    }
    *p = 0;
    for ( pa = p - 1; head < pa; --pa )
    {
      temp = *head;
      *head = *pa;
      *pa = temp;
      ++head;
    }
    return stra;
  }
  else
  {
    pb = stra + 1;
    *stra = 48;
    *pb = 0;
    return pb;
  }
}