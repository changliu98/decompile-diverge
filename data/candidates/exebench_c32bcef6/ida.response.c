void __cdecl copy(char *to, char *from)
{
  char v2; // al
  int i; // [rsp+0h] [rbp-14h]

  for ( i = 0; ; ++i )
  {
    v2 = from[i];
    to[i] = v2;
    if ( !v2 )
      break;
  }
}