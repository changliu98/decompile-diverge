int __cdecl sdsull2str(char *s, unsigned __int64 v)
{
  char *v2; // rax
  int l; // [rsp+0h] [rbp-28h]
  char aux; // [rsp+Fh] [rbp-19h]
  char *p; // [rsp+10h] [rbp-18h]
  char *pa; // [rsp+10h] [rbp-18h]
  char *sa; // [rsp+20h] [rbp-8h]

  sa = s;
  p = s;
  do
  {
    v2 = p++;
    *v2 = v % 0xA + 48;
    v /= 0xAuLL;
  }
  while ( v );
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