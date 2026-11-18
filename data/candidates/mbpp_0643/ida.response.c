char *__cdecl func0(const char *text)
{
  char msgbuf[100]; // [rsp+0h] [rbp-C0h] BYREF
  int reti; // [rsp+64h] [rbp-5Ch]
  char *pattern; // [rsp+68h] [rbp-58h]
  regex_t regex; // [rsp+70h] [rbp-50h] BYREF
  const char *texta; // [rsp+B0h] [rbp-10h]

  texta = text;
  pattern = "\\Bz\\B";
  if ( regcomp(&regex, "\\Bz\\B", 1) )
  {
    fprintf(stderr, "Could not compile regex\n");
    return "Regex compilation error";
  }
  else
  {
    reti = regexec(&regex, texta, 0LL, 0LL, 0);
    if ( reti )
    {
      if ( reti == 1 )
      {
        return "Not matched!";
      }
      else
      {
        regerror(reti, &regex, msgbuf, 0x64uLL);
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return "Regex execution error";
      }
    }
    else
    {
      return "Found a match!";
    }
  }
}