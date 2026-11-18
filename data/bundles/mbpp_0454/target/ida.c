const char *__cdecl func0(const char *text)
{
  char error_message[100]; // [rsp+0h] [rbp-D0h] BYREF
  char *pattern; // [rsp+70h] [rbp-60h]
  int reti; // [rsp+7Ch] [rbp-54h]
  regex_t regex; // [rsp+80h] [rbp-50h] BYREF
  const char *texta; // [rsp+C0h] [rbp-10h]

  texta = text;
  pattern = "\\w*z.\\w*";
  if ( regcomp(&regex, "\\w*z.\\w*", 1) )
  {
    fprintf(stderr, "Could not compile regex\n");
    return "Regex compile error";
  }
  else
  {
    reti = regexec(&regex, texta, 0LL, 0LL, 0);
    regfree(&regex);
    if ( reti )
    {
      if ( reti == 1 )
      {
        return "Not matched!";
      }
      else
      {
        regerror(reti, &regex, error_message, 0x64uLL);
        fprintf(stderr, "Regex match failed: %s\n", error_message);
        return "Regex match error";
      }
    }
    else
    {
      return "Found a match!";
    }
  }
}