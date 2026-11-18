char *func0(char *text)
{
 int err;
 regex_t regex;
 regmatch_t match;
 char *bufptr = func0::buffer;
 char *text_local = text;

 if (err = regcomp(&regex, " +", 1))
  return NULL;

 while (*text_local) {
  if (err = regexec(&regex, text_local, 1, &match, 0)) {
   strcpy(bufptr, text_local);
   break;
  }
  memcpy(bufptr, text_local, match.rm_so);
  bufptr += match.rm_so;
  *bufptr++ = ' ';
  text_local += match.rm_eo;
 }

 regfree(&regex);

 return func0::buffer;
}