const char *
func0(const char *str)
{
  regex_t re;
  int reti;
  const char *text = str;
  char msgbuf[100];

  reti = regcomp(&re, "\\w*z.\\w*", 0x01);
  if (reti) {
    fprintf(PTR_stderr_00103ff8, "Could not compile regex\n");
    return "Regex compile error";
  }
  reti = regexec(&re, text, 0, NULL, 0);
  regfree(&re);
  if (!reti) {
    return "Found a match!";
  } else if (reti == 1) {
    return "Not matched!";
  }
  regerror(reti, &re, msgbuf, sizeof(msgbuf));
  fprintf(PTR_stderr_00103ff8, "Regex match failed: %s\n", msgbuf);
  return "Regex match error";
}