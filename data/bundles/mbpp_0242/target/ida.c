int __cdecl func0(const char *str1)
{
  int total; // [rsp+0h] [rbp-Ch]

  total = 0;
  while ( *str1 )
  {
    ++total;
    ++str1;
  }
  return total;
}