int __cdecl sdsll2str(char *s, __int64 value)
{
  char *v2; // rax
  char *v3; // rax
  int l; // [rsp+0h] [rbp-30h]
  unsigned __int64 v; // [rsp+8h] [rbp-28h]
  char aux; // [rsp+17h] [rbp-19h]
  char *p; // [rsp+18h] [rbp-18h]
  char *pa; // [rsp+18h] [rbp-18h]
  char *sa; // [rsp+28h] [rbp-8h]

  sa = s;
  if ( value >= 0 )
  {
    v = value;
  }
  else if ( value == 0x8000000000000000LL )
  {
    v = 0x8000000000000000LL;
  }
  else
  {
    v = -value;
  }
  p = s;
  do
  {
    v2 = p++;
    *v2 = v % 0xA + 48;
    v /= 0xAuLL;
  }
  while ( v );
  if ( value < 0 )
  {
    v3 = p++;
    *v3 = 45;
  }
  l = (_DWORD)p - (_DWORD)s;
  *p = 0;
  for ( pa = p - 1; sa < pa; --pa )
  {
    aux = *sa;
    *sa = *pa;
    *pa = aux;
    ++sa;
  }
  return l;
}