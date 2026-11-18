const char *
func0(const char *str)
{
  regex_t re;
  int reti;
  const char *text = str;
  char msgbuf[100];

  reti = regcomp(&re, "\\Bz\\B", 0x00000001);
  if (reti) {
    fprintf(PTR_stderr_00103ff8, "Could not compile regex\n");
    return "Regex compilation error";
  }

  reti = regexec(&re, text, 0, NULL, 0);
  if (!reti) {
    return "Found a match!";
  } else if (reti == 1) {
    return "Not matched!";
  } else {
    regerror(reti, &re, msgbuf, sizeof(msgbuf));
    fprintf(PTR_stderr_00103ff8, "Regex match failed: %s\n", msgbuf);
    return "Regex execution error";
  }
}