char *func0(char *text)
{
 int reti;
 regex_t re;
 regmatch_t matches[1];
 char word[100];

 reti = regcomp(&re, "\\w+ly", 1);
 if (reti) {
  printf("Could not compile regex\n");
  return NULL;
 }

 reti = regexec(&re, text, 1, matches, 0);
 if (!reti) {
  strncpy(word, text + matches[0].rm_so,
   matches[0].rm_eo - matches[0].rm_so);
  word[matches[0].rm_eo - matches[0].rm_so] = '\0';
  snprintf(func0::result, 100, "%d-%d: %s",
   matches[0].rm_so, matches[0].rm_eo, word);
  regfree(&re);
  return func0::result;
 }

 regfree(&re);
 return NULL;
}