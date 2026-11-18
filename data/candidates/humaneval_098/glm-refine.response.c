int __cdecl func0(const char *s)
{
  int count = 0;
  int len = strlen(s);
  
  for (int i = 0; i * 2 < len; ++i)
  {
    if (strchr("AEIOU", s[i * 2]))
    {
      ++count;
    }
  }
  
  return count;
}