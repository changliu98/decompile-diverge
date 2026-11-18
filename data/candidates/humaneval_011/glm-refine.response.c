char *__cdecl func0(const char *str1, const char *str2)
{
  int min_len;
  int i;
  char *output;
  int len_str2;
  int len_str1;

  len_str1 = strlen(str1);
  len_str2 = strlen(str2);
  
  // Find the minimum length of the two strings
  min_len = (len_str1 < len_str2) ? len_str1 : len_str2;
  
  output = (char *)malloc(min_len + 1);
  if (!output)
    return 0LL;
    
  // Compare characters up to the minimum length
  for (i = 0; i < min_len; ++i)
  {
    // If characters match, output '0' (ASCII 48), otherwise '1' (ASCII 49)
    output[i] = (str1[i] == str2[i]) ? '0' : '1';
  }
  
  output[min_len] = '\0';
  return output;
}