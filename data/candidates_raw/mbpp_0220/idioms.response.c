char *func0(char *text, int n)
{
  int i;
  int num_replacements;
  int match;
  char *new_text = text;
  int max_replacements = n;
  char *re = "[ ,.]";
  struct regex_t re_id;
  struct regmatch_t match_id[1];
  strcpy(func0_new_text, text);
  regcomp(&re_id, re, 1);
  for (num_replacements = 0; (num_replacements < max_replacements); num_replacements++)
  {
    match = 0;
    if (num_replacements < max_replacements)
    {
      match = (regexec(&re_id, func0_new_text, 1, match_id, 0)) == 0 ? 1 : 0;
    }
    if (match == 0)
    {
      break;
    }
    func0_new_text[match_id[0].rm_so] = ':';
  }
  regfree(&re_id);
  return func0_new_text;
}