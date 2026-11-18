void __cdecl reverse(char *s)
{
  char v1; // al
  char v2; // al
  char *q; // [rsp+0h] [rbp-18h]
  char *qa; // [rsp+0h] [rbp-18h]
  char *p; // [rsp+8h] [rbp-10h]

  q = s;
  p = s;
  while ( *q )
    ++q;
  for ( qa = q - 1; p < qa; --qa )
  {
    v1 = *qa ^ *p;
    *p = v1;
    v2 = v1 ^ *qa;
    *qa = v2;
    *p++ ^= v2;
  }
}