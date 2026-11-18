const char *
func0(const char *str)
{
  regex_t re;
  int reti;

  reti = regcomp(&re, "^[a-z]$|^([a-z]).*\\1$", 0x01);
  if (reti)
    {
      fprintf(PTR_stderr_00103ff8, "Could not compile regex\n");
      return "Invalid";
    }

  reti = regexec(&re, str, 0, NULL, 0);
  if (!reti)
    {
      regfree(&re);
      return "Valid";
    }
  else if (reti == 1)
    {
      regfree(&re);
      return "Invalid";
    }

  char msgbuf[100];
  regerror(reti, &re, msgbuf, sizeof(msgbuf));
  fprintf(PTR_stderr_00103ff8, "Regex match failed: %s\n", msgbuf);
  regfree(&re);
  return "Invalid";
}