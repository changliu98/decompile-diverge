void __cdecl break_atr(char *str, char c)
{
  char *p; // [rsp+8h] [rbp-18h]

  p = strrchr(str, c);
  if ( p )
    *p = 0;
}