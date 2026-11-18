void __cdecl string_reverse(char *s)
{
  char *v1; // rax
  char v2; // cl
  char *v3; // rax
  char c; // [rsp+0h] [rbp-14h]
  char *t; // [rsp+4h] [rbp-10h]
  char *sa; // [rsp+Ch] [rbp-8h]

  sa = s;
  for ( t = s; *t; ++t )
    ;
  while ( sa < t )
  {
    c = *sa;
    v1 = t--;
    v2 = *(v1 - 1);
    v3 = sa++;
    *v3 = v2;
    *t = c;
  }
}