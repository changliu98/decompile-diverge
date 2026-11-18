bool __cdecl func0(const char *s0, const char *s1)
{
  int len0 = strlen(s0);
  int len1 = strlen(s1);

  // Check if every character in s0 exists in s1
  for (int i = 0; i < len0; ++i)
  {
    bool found = false;
    for (int j = 0; j < len1; ++j)
    {
      if (s0[i] == s1[j])
      {
        found = true;
        break;
      }
    }
    if (!found)
      return false;
  }

  // Check if every character in s1 exists in s0
  for (int i = 0; i < len1; ++i)
  {
    bool found = false;
    for (int j = 0; j < len0; ++j)
    {
      if (s1[i] == s0[j])
      {
        found = true;
        break;
      }
    }
    if (!found)
      return false;
  }

  return true;
}