int wc_match(const char *wc, const char *str, size_t len)
{
 int ret;
 int match;
 const char *end = str + len;

 if (*wc != '*') {
  match = wc_match_fragment(&wc, &str, end);
  if (match <= 0) {
   ret = match;
   goto out;
  }
 }

 while (1) {
  if (!*wc) {
   ret = (str == end ? 1 : 0);
   goto out;
  }

  do { if (!(*wc == '*')) ___assert_fail("*wildcard == '*'", "./func.c", 228, "int wc_match_inner(const char *, const char *, size_t)"); } while (0);

  while (*wc == '*')
   wc++;

  if (!*wc) {
   ret = 1;
   goto out;
  }

  match = 0;

  while (*str) {
   const char *save_w = wc;
   const char *save_t = str;
   match = wc_match_fragment(&wc, &str, end);
   if (match < 0) {
    ret = match;
    goto out;
   }
   if (match > 0 && !*wc && str != end) {
    str = end - (save_t - str);
    wc = save_w;
    ret = wc_match_fragment(&wc, &str, end);
    goto out;
   }
   if (match > 0)
    break;
   str++;
  }

  if (match > 0)
   continue;

  str++;
 }

out:
 return ret;
}