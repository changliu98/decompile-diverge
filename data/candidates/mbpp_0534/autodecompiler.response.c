int func0(char *pattern, char *string, int *begin, int *end)
{
 regex_t regex;
 regmatch_t match[1];
 int status;

 if (regcomp(&regex, pattern, 1) != 0)
 {
  return(-1);
 }
 status = regexec(&regex, string, 1, match, 0);
 regfree(&regex);
 if (status != 0)
 {
  return(-1);
 }
 *begin = match[0].rm_so;
 *end = match[0].rm_eo;
 return(0);
}