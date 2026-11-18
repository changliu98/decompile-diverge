char *__cdecl func0(const char *string, const char *sample)
{
  char pattern[100]; // [rsp+0h] [rbp-C0h] BYREF
  int result; // [rsp+64h] [rbp-5Ch]
  regex_t regex; // [rsp+68h] [rbp-58h] BYREF
  const char *samplea; // [rsp+A8h] [rbp-18h]
  const char *stringa; // [rsp+B0h] [rbp-10h]

  stringa = string;
  samplea = sample;
  if ( !strstr(string, sample) )
    return "entered string isnt a substring";
  memset(pattern, 0, sizeof(pattern));
  pattern[0] = 94;
  strcat(pattern, samplea);
  regcomp(&regex, pattern, 0);
  result = regexec(&regex, stringa, 0LL, 0LL, 0);
  regfree(&regex);
  if ( result )
    return "string doesnt start with the given substring";
  else
    return "string starts with the given substring";
}