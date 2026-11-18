void __cdecl reverse(char *s)
{
  char tmp; // [rsp+1h] [rbp-11h]
  char *t; // [rsp+2h] [rbp-10h]
  char *ta; // [rsp+2h] [rbp-10h]
  char *sa; // [rsp+Ah] [rbp-8h]

  sa = s;
  for ( t = s; *t; ++t )
    ;
  for ( ta = t - 1; sa < ta; --ta )
  {
    tmp = *sa;
    *sa = *ta;
    *ta = tmp;
    ++sa;
  }
}