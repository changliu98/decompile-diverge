char *func0(char *str, int n)
{
  int i;
  int pos;
  char *p;
  regex_t reg;
  regmatch_t match[1];

  strcpy(func0_new_text, str);

  p = "[ ,.]";
  regcomp(&reg, p, 1);

  for (i=0;;i++) {
    if ((i >= n) || !regexec(&reg, func0_new_text, 1, match, 0)) break;
    pos = match[0].rm_so;
    func0_new_text[pos] = ':';
  }

  regfree(&reg);
  return func0_new_text;
}