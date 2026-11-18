char *__cdecl func0(const char *str1)
{
  int j = 0;
  int len = strlen(str1);

  // Iterate through the string 1-based, acting on odd indices
  for (int i = 1; i <= len; ++i)
  {
    if (i % 2)
    {
      // i is 1-based and odd, so i-1 corresponds to 0-based even indices (0, 2, 4...)
      func0_str2[j++] = str1[i - 1];
    }
  }
  
  func0_str2[j] = '\0';
  return func0_str2;
}