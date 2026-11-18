bool __cdecl func0(const char *string)
{
  bool match_found; // [rsp+3h] [rbp-4Dh]
  regex_t regex; // [rsp+8h] [rbp-48h] BYREF
  const char *stringa; // [rsp+48h] [rbp-8h]

  stringa = string;
  regcomp(&regex, ".*[0-9]$", 0);
  match_found = regexec(&regex, stringa, 0LL, 0LL, 0) == 0;
  regfree(&regex);
  return match_found;
}