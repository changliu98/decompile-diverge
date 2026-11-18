void __cdecl reverse(char *s)
{
  char c; // [rsp+1h] [rbp-11h]
  char *s0; // [rsp+2h] [rbp-10h]
  char *sa; // [rsp+Ah] [rbp-8h]
  char *sb; // [rsp+Ah] [rbp-8h]

  sa = s;
  s0 = s;
  while ( *sa )
    ++sa;
  for ( sb = sa - 1; s0 < sb; --sb )
  {
    c = *s0;
    *s0 = *sb;
    *sb = c;
    ++s0;
  }
}