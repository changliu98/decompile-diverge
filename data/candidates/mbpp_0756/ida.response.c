const char *__cdecl func0(const char *text)
{
  const char *result; // [rsp+0h] [rbp-60h]
  regex_t regex; // [rsp+10h] [rbp-50h] BYREF
  const char *texta; // [rsp+50h] [rbp-10h]

  texta = text;
  if ( regcomp(&regex, "ab?", 1) )
    return "Not matched!";
  if ( regexec(&regex, texta, 0LL, 0LL, 0) )
    result = "Not matched!";
  else
    result = "Found a match!";
  regfree(&regex);
  return result;
}