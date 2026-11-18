int __cdecl func0(char **lst, int size)
{
  int i; // [rsp+8h] [rbp-18h]

  for ( i = 1; i < size; ++i )
  {
    if ( strcmp(*lst, lst[i]) )
      return 0;
  }
  return 1;
}