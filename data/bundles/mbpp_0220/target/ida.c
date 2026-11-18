char *__cdecl func0(const char *text, int n)
{
  bool v3; // [rsp+7h] [rbp-69h]
  int num_replacements; // [rsp+Ch] [rbp-64h]
  regmatch_t pmatch[1]; // [rsp+18h] [rbp-58h] BYREF
  regex_t regex; // [rsp+20h] [rbp-50h] BYREF
  int na; // [rsp+64h] [rbp-Ch]
  const char *texta; // [rsp+68h] [rbp-8h]

  texta = text;
  na = n;
  strcpy(func0_new_text, text);
  regcomp(&regex, "[ ,.]", 1);
  for ( num_replacements = 0; ; ++num_replacements )
  {
    v3 = 0;
    if ( num_replacements < na )
      v3 = regexec(&regex, func0_new_text, 1uLL, pmatch, 0) == 0;
    if ( !v3 )
      break;
    func0_new_text[pmatch[0].rm_so] = 58;
  }
  regfree(&regex);
  return func0_new_text;
}