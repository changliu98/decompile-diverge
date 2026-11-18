char *__cdecl func0(char *str1)
{
  int j = 0;
  int len = strlen(str1);

  // Iterate through the string 1-indexed up to the string length
  for (int i = 1; i <= len; ++i)
  {
    // Check if the 1-based index is even
    if (i % 2 == 0)
    {
      // Store the character from the even 1-based index (which is the odd 0-based index)
      func0_str2[j++] = str1[i - 1];
    }
  }
  
  // Null-terminate the destination string
  func0_str2[j] = '\0';
  
  return func0_str2;
}