void __cdecl func0(const char *str1, char *result)
{
  char *cursor; // [rsp+8h] [rbp-478h]
  char buffer[1024]; // [rsp+10h] [rbp-470h] BYREF
  regmatch_t matches[3]; // [rsp+410h] [rbp-70h] BYREF
  regex_t regex; // [rsp+430h] [rbp-50h] BYREF
  char *resulta; // [rsp+470h] [rbp-10h]
  const char *str1a; // [rsp+478h] [rbp-8h]

  str1a = str1;
  resulta = result;
  regcomp(&regex, "([a-z])([A-Z])", 1);
  strcpy(buffer, str1a);
  cursor = buffer;
  *resulta = 0;
  while ( !regexec(&regex, cursor, 3uLL, matches, 0) )
  {
    strncat(resulta, cursor, matches[1].rm_eo);
    strcat(resulta, " ");
    cursor += matches[2].rm_so;
  }
  strcat(resulta, cursor);
  regfree(&regex);
}