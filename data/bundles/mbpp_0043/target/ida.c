char *__cdecl func0(const char *text)
{
  char errorMessage[100]; // [rsp+0h] [rbp-D0h] BYREF
  char *patterns; // [rsp+70h] [rbp-60h]
  int regexSearch; // [rsp+78h] [rbp-58h]
  regex_t regex; // [rsp+80h] [rbp-50h] BYREF
  const char *texta; // [rsp+C0h] [rbp-10h]

  texta = text;
  patterns = "^[a-z]+_[a-z]+$";
  if ( regcomp(&regex, "^[a-z]+_[a-z]+$", 1) )
  {
    fprintf(stderr, "Could not compile regex\n");
    return "Compilation error";
  }
  else
  {
    regexSearch = regexec(&regex, texta, 0LL, 0LL, 0);
    if ( regexSearch )
    {
      if ( regexSearch == 1 )
      {
        regfree(&regex);
        return "Not matched!";
      }
      else
      {
        regerror(regexSearch, &regex, errorMessage, 0x64uLL);
        fprintf(stderr, "Regex match failed: %s\n", errorMessage);
        regfree(&regex);
        return "Error occurred";
      }
    }
    else
    {
      regfree(&regex);
      return "Found a match!";
    }
  }
}