char *__cdecl func0(const char *string)
{
  char msgbuf[100]; // [rsp+0h] [rbp-C0h] BYREF
  int reti; // [rsp+6Ch] [rbp-54h]
  regex_t regex; // [rsp+70h] [rbp-50h] BYREF
  const char *stringa; // [rsp+B0h] [rbp-10h]

  stringa = string;
  if ( regcomp(&regex, "^[a-z]$|^([a-z]).*\\1$", 1) )
  {
    fprintf(stderr, "Could not compile regex\n");
    return "Invalid";
  }
  else
  {
    reti = regexec(&regex, stringa, 0LL, 0LL, 0);
    if ( reti )
    {
      if ( reti == 1 )
      {
        regfree(&regex);
      }
      else
      {
        regerror(reti, &regex, msgbuf, 0x64uLL);
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        regfree(&regex);
      }
      return "Invalid";
    }
    else
    {
      regfree(&regex);
      return "Valid";
    }
  }
}