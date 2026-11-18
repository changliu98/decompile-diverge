bool __cdecl func0(const char *string)
{
  int result; // [rsp+Ch] [rbp-54h]
  regex_t regex; // [rsp+10h] [rbp-50h] BYREF
  const char *stringa; // [rsp+50h] [rbp-10h]

  stringa = string;
  if ( regcomp(&regex, "^5", 0) )
  {
    fprintf(stderr, "Could not compile regex\n");
    return 0;
  }
  else
  {
    result = regexec(&regex, stringa, 0LL, 0LL, 0);
    regfree(&regex);
    return result == 0;
  }
}