int __cdecl reverse(char *s)
{
  char *v1; // rax
  char v2; // al
  char v3; // al
  char *q; // [rsp+0h] [rbp-18h]
  char *qa; // [rsp+0h] [rbp-18h]
  char *p; // [rsp+8h] [rbp-10h]

  p = s;
  q = s;
  do
    v1 = q++;
  while ( *v1 );
  for ( qa = q - 2; p < qa; --qa )
  {
    v2 = *qa ^ *p;
    *p = v2;
    v3 = v2 ^ *qa;
    *qa = v3;
    *p++ ^= v3;
  }
  return 0;
}