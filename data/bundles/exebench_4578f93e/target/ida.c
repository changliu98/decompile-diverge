char *__cdecl mystrncpy(char *dest, char *src, int n)
{
  char *v3; // rax
  char v4; // cl
  char *v5; // rax
  bool v7; // [rsp+1h] [rbp-21h]
  int i; // [rsp+Ah] [rbp-18h]
  char *desta; // [rsp+1Ah] [rbp-8h]

  desta = dest;
  for ( i = 0; ; ++i )
  {
    v7 = 0;
    if ( i < n )
      v7 = *src != 0;
    if ( !v7 )
      break;
    v3 = src++;
    v4 = *v3;
    v5 = desta++;
    *v5 = v4;
  }
  *desta = 0;
  return dest;
}