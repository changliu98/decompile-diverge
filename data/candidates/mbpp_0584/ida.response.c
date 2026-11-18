char *__cdecl func0(const char *text)
{
  char word[100]; // [rsp+0h] [rbp-D0h] BYREF
  int end; // [rsp+70h] [rbp-60h]
  int start; // [rsp+74h] [rbp-5Ch]
  regmatch_t match[1]; // [rsp+78h] [rbp-58h] BYREF
  regex_t regex; // [rsp+80h] [rbp-50h] BYREF
  const char *texta; // [rsp+C0h] [rbp-10h]

  texta = text;
  if ( regcomp(&regex, "\\w+ly", 1) )
  {
    printf("Could not compile regex\n");
    return 0LL;
  }
  else if ( regexec(&regex, texta, 1uLL, match, 0) )
  {
    regfree(&regex);
    return 0LL;
  }
  else
  {
    start = match[0].rm_so;
    end = match[0].rm_eo;
    strncpy(word, &texta[match[0].rm_so], match[0].rm_eo - match[0].rm_so);
    word[end - start] = 0;
    snprintf(func0_result, 0x64uLL, "%d-%d: %s", (unsigned int)start, (unsigned int)end, word);
    regfree(&regex);
    return func0_result;
  }
}