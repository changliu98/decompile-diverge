void __cdecl break_at(char *str, char c)
{
  char *p; // [rsp+8h] [rbp-18h]

  p = strchr(str, c);
  if ( p )
    *p = 0;
}