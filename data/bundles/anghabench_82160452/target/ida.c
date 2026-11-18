int __cdecl sdsll2str(char *s, __int64 value)
{
  char *v2; // rax
  char *v3; // rax
  __int64 v5; // [rsp+0h] [rbp-38h]
  int l; // [rsp+8h] [rbp-30h]
  unsigned __int64 v; // [rsp+10h] [rbp-28h]
  char aux; // [rsp+1Fh] [rbp-19h]
  char *p; // [rsp+20h] [rbp-18h]
  char *pa; // [rsp+20h] [rbp-18h]
  char *sa; // [rsp+30h] [rbp-8h]

  sa = s;
  if ( value >= 0 )
    v5 = value;
  else
    v5 = -value;
  v = v5;
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