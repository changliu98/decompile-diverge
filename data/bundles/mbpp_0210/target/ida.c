bool __cdecl func0(const char *string)
{
  int result; // [rsp+4h] [rbp-4Ch]
  regex_t regex; // [rsp+8h] [rbp-48h] BYREF
  const char *stringa; // [rsp+48h] [rbp-8h]

  stringa = string;
  regcomp(&regex, "[^a-zA-Z0-9.]", 1);
  result = regexec(&regex, stringa, 0LL, 0LL, 0);
  regfree(&regex);
  return result == 1;
}