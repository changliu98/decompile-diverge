const char *__cdecl string_to_slong(const char *s, long *number)
{
  const char *v2; // rax
  int c; // [rsp+0h] [rbp-18h]
  int sign; // [rsp+4h] [rbp-14h]
  const char *sa; // [rsp+10h] [rbp-8h]

  sa = s;
  c = *s;
  if ( c == 45 )
  {
    sign = 1;
    sa = s + 1;
    c = s[1];
  }
  else
  {
    sign = 0;
    if ( c == 43 )
    {
      sa = s + 1;
      c = s[1];
    }
  }
  *number = 0LL;
  while ( (unsigned int)(c - 48) <= 9 )
  {
    *number = c - 48 + 10 * *number;
    v2 = sa++;
    c = v2[1];
  }
  if ( sign )
    *number = -*number;
  return sa;
}