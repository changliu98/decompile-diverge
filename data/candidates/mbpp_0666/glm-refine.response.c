int __cdecl func0(const char *string, char c)
{
  int count = 0;
  size_t length = strlen(string);

  for (size_t i = 0; i < length; ++i)
  {
    if (string[i] == c)
      ++count;
  }
  
  return count;
}