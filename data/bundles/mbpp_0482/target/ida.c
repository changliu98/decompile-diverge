char *__cdecl func0(char *text)
{
  int result; // [rsp+Ch] [rbp-54h]
  regex_t regex; // [rsp+10h] [rbp-50h] BYREF
  char *texta; // [rsp+50h] [rbp-10h]

  texta = text;
  regcomp(&regex, "[A-Z]+[a-z]+$", 1);
  result = regexec(&regex, texta, 0LL, 0LL, 0);
  regfree(&regex);
  if ( result )
    return "No";
  else
    return "Yes";
}