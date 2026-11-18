char *__cdecl func0(char *text)
{
  regex_t regex; // [rsp+10h] [rbp-50h] BYREF
  char *texta; // [rsp+50h] [rbp-10h]

  texta = text;
  regcomp(&regex, "[A-Z]+[a-z]+$", 1);
  if ( regexec(&regex, texta, 0LL, 0LL, 0) )
    return "Not matched!";
  else
    return "Found a match!";
}