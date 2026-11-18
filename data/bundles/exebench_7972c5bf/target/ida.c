void __cdecl tagcpy(char *dest, char *src, int tag_size)
{
  char *v3; // rax
  char v4; // cl
  char *v5; // rax
  bool v6; // [rsp+1h] [rbp-29h]
  char *s2; // [rsp+2h] [rbp-28h]
  char *s1; // [rsp+Ah] [rbp-20h]

  s1 = src;
  s2 = &src[tag_size - 1];
  if ( *s2 && !src[tag_size - 2] )
    s2 = &src[tag_size - 2];
  while ( s1 <= s2 )
  {
    if ( *s1 == 32 )
    {
      ++s1;
    }
    else
    {
      if ( *s2 && *s2 != 32 )
        goto LABEL_10;
      --s2;
    }
  }
  while ( 1 )
  {
LABEL_10:
    v6 = 0;
    if ( *s1 )
      v6 = s1 <= s2;
    if ( !v6 )
      break;
    v3 = s1++;
    v4 = *v3;
    v5 = dest++;
    *v5 = v4;
  }
  *dest = 0;
}