bool __cdecl contains_substring(const char **strings, const char *substring, int count)
{
  for (int i = 0; i < count; ++i)
  {
    if (strstr(strings[i], substring))
      return true;
  }
  return false;
}