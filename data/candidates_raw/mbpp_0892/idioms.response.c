char *strltrim(char *text)
{
  char *textp = text;
  char *ret = textp;
  char *buf = func0_buffer;
  struct regex r;
  struct regmatch_t match;
  if (regcomp(&r, " +", 1))
    return ((void *)0);
  while (*textp) {
    if (regexec(&r, textp, 1, &match, 0)) {
      strcpy(buf, textp);
      break;
    }
    memcpy(buf, textp, match.rm_so);
    buf[match.rm_so++] = ' ';
    textp += match.rm_eo;
  }
  regfree(&r);
  return func0_buffer;
}