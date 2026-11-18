char *__cdecl str_rev(char *s)
{
  char *v1; // rax
  char *v2; // rax
  char *v3; // rax
  char ch_0; // [rsp+1h] [rbp-19h]
  char *t; // [rsp+2h] [rbp-18h]
  char *ta; // [rsp+2h] [rbp-18h]
  char *h; // [rsp+Ah] [rbp-10h]

  h = s;
  t = s;
  do
    v1 = t++;
  while ( *v1 );
  for ( ta = t - 2; h < ta; --ta )
  {
    ch_0 = *h;
    v2 = h++;
    *v2 = *ta;
    v3 = ta;
    *v3 = ch_0;
  }
  return s;
}