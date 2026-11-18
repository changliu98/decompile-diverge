char *__cdecl func0(char *str, char char_to_remove)
{
  int remove_count = 0;
  
  // First pass: count the occurrences of the target character
  for (int i = 0; str[i]; ++i)
  {
    if (str[i] == char_to_remove)
      ++remove_count;
  }

  // Allocate memory for the new string (original length - removed characters + null terminator)
  char *result = (char *)malloc(strlen(str) - remove_count + 1);
  
  // Second pass: copy over characters that are not the target character
  int j = 0;
  for (int i = 0; str[i]; ++i)
  {
    if (str[i] != char_to_remove)
      result[j++] = str[i];
  }
  
  result[j] = '\0';
  return result;
}