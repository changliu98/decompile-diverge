char *__cdecl func0(char *str)
{
  int j = 0;

  // Iterate through the string, extracting characters at even indices (0, 2, 4...)
  for (int i = 0; i < strlen(str); ++i)
  {
    if (i % 2 == 0)
    {
      func0_result[j++] = str[i];
    }
  }
  
  // Null-terminate the resulting string
  func0_result[j] = '\0';
  
  return func0_result;
}