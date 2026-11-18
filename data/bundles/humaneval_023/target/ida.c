int __cdecl func0(const char *str)
{
  int length; // [rsp+0h] [rbp-Ch]

  for ( length = 0; str[length]; ++length )
    ;
  return length;
}