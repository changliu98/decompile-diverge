void __cdecl reverse(char *str)
{
  char *v1; // rax
  char *q; // [rsp+0h] [rbp-10h]
  char *qa; // [rsp+0h] [rbp-10h]
  char *stra; // [rsp+8h] [rbp-8h]

  stra = str;
  q = str;
  do
    v1 = q++;
  while ( *v1 );
  for ( qa = q - 2; stra < qa; --qa )
  {
    *stra -= *qa;
    *qa += *stra;
    *stra = *qa - *stra;
    ++stra;
  }
}