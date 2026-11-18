char* func0(char* text)
{
 regex_t regex;
 int reti;
 char msgbuf[100];

 reti = regcomp(&regex, "^[a-z]+_[a-z]+$", 0x01);
 if (reti) {
  fprintf(PTR_stderr_00103ff8, "Could not compile regex\n");
  return "Compilation error";
 }

 reti = regexec(&regex, text, 0, NULL, 0);
 if (!reti) {
  regfree(&regex);
  return "Found a match!";
 } else if (reti == 1) {
  regfree(&regex);
  return "Not matched!";
 }

 regerror(reti, &regex, msgbuf, sizeof(msgbuf));
 fprintf(PTR_stderr_00103ff8, "Regex match failed: %s\n", msgbuf);
 regfree(&regex);

 return "Error occurred";
}