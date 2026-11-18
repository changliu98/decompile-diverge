void __cdecl copy_string(char *dst, char *src, int max)
{
  char v3; // al
  bool v4; // [rsp+1h] [rbp-19h]
  int i; // [rsp+2h] [rbp-18h]

  for ( i = 0; ; ++i )
  {
    v4 = 0;
    if ( i < max )
    {
      v3 = src[i];
      dst[i] = v3;
      v4 = v3 != 0;
    }
    if ( !v4 )
      break;
  }
}