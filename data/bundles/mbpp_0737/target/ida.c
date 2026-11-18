char *__cdecl func0(char *string)
{
  int result; // [rsp+Ch] [rbp-54h]
  regex_t regex; // [rsp+10h] [rbp-50h] BYREF
  char *stringa; // [rsp+50h] [rbp-10h]

  stringa = string;
  regcomp(&regex, "^[aeiouAEIOU][A-Za-z0-9_]*", 9);
  result = regexec(&regex, stringa, 0LL, 0LL, 0);
  regfree(&regex);
  if ( result )
    return "Invalid";
  else
    return "Valid";
}