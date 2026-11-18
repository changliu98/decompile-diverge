char *func0(char *str)
{
 char *p, *s;
 regex_t re;
 regmatch_t match[1];
 int err;

 s = str;
 p = func0_buffer;

 if ((err = regcomp(&re, " +", 1)) != 0) {
  char msg[100];
  (void) sprintf__bench(msg, "regcomp() failed: %d", err);
  return msg;
 }

 while (*s != '\0') {
  if (regexec(&re, s, 1, match, 0) == 0) {

   memcpy(p, s, match[0].rm_so);
   p += match[0].rm_so;
   *p++ = ' ';

   s += match[0].rm_eo;
  } else {

   strcpy(p, s);
   break;
  }
 }
 regfree(&re);

 return func0_buffer;
}