const char *__cdecl func0(const char *text)
{
  char err_buf[100]; 
  int ret;
  regex_t regex;

  // Compile the regex pattern "\Bz\B" with REG_EXTENDED (flag 1)
  if (regcomp(&regex, "\\Bz\\B", REG_EXTENDED))
  {
    fprintf(stderr, "Could not compile regex\n");
    return "Regex compilation error";
  }

  // Execute the regex against the input text
  ret = regexec(&regex, text, 0, NULL, 0);
  
  if (ret == 0)
  {
    return "Found a match!";
  }
  
  if (ret == REG_NOMATCH) // Equivalent to ret == 1
  {
    return "Not matched!";
  }

  // Handle any other execution errors
  regerror(ret, &regex, err_buf, sizeof(err_buf));
  fprintf(stderr, "Regex match failed: %s\n", err_buf);
  return "Regex execution error";
}