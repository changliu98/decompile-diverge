void __cdecl copy(char *longest, char *line)
{
  char v2; // al
  int i; // [rsp+0h] [rbp-14h]

  for ( i = 0; ; ++i )
  {
    v2 = line[i];
    longest[i] = v2;
    if ( !v2 )
      break;
  }
}