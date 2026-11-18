int __cdecl func0(const char *str1)
{
  int count; // [rsp+0h] [rbp-Ch]

  count = 0;
  while ( *str1 )
  {
    ++count;
    ++str1;
  }
  return count;
}