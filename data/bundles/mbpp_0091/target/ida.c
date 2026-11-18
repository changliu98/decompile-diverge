bool __cdecl func0(char **str1, char *sub_str, int size)
{
  int i; // [rsp+0h] [rbp-20h]

  for ( i = 0; i < size; ++i )
  {
    if ( strstr(str1[i], sub_str) )
      return 1;
  }
  return 0;
}