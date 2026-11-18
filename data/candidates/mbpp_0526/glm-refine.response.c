Optimized and annotated version
char *__cdecl func0(const char *str1)
{
  size_t i;
  char *result;
  size_t len;

  len = strlen(str1);
  
  // Allocate memory for the new string plus the null terminator
  result = (char *)malloc(len + 1);
  if (!result)
    return NULL;

  if (len > 0)
  {
    // Capitalize the first character
    result[0] = toupper(str1[0]);
    
    // Lowercase the remaining characters
    for (i = 1; i < len; ++i)
      result[i] = tolower(str1[i]);
      
    // Capitalize the last character (overwriting the previous lowercase)
    result[len - 1] = toupper(result[len - 1]);
    
    // Ensure null-termination
    result[len] = '\0';
  }
  
  return result;
}