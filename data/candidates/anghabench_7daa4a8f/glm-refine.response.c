char *__cdecl stb_skipnewline(char *s)
{
  char *sa = s;

  // Check if the current character is a newline (\r = 13 or \n = 10)
  if (*s == '\r' || *s == '\n')
  {
    // If the current and next characters form a \r\n or \n\r sequence, 
    // skip the first character. (13 + 10 = 23)
    if (*s + s[1] == 23)
      sa = s + 1;
      
    // Skip the newline character itself
    ++sa;
  }
  
  return sa;
}