int __cdecl func0(const char *s, char c)
{
  int count = 0;
  size_t length = strlen(s);

  for (size_t i = 0; i < length; ++i)
  {
    if (s[i] == c)
    {
      ++count;
    }
  }
  
  return count;
}