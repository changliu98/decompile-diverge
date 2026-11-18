char *__cdecl func0(const char *text)
{
  int result; // [rsp+Ch] [rbp-54h]
  regex_t regex; // [rsp+10h] [rbp-50h] BYREF
  const char *texta; // [rsp+50h] [rbp-10h]

  texta = text;
  if ( regcomp(&regex, "a.*?b$", 1) )
    return "Regex compilation failed.";
  result = regexec(&regex, texta, 0LL, 0LL, 0);
  if ( !result )
    return "Found a match!";
  if ( result == 1 )
    return "Not matched!";
  return "Regex match failed.";
}