const char *
func0(const char *patterns[], int pattern_n, const char *text)
{
 int i;
 regex_t regex;
 int ret;

 for (i = 0; i < pattern_n; i++) {
  ret = regcomp(&regex, patterns[i], 0);
  if (ret) {
   fprintf(*PTR_stderr_00103ff8, "Could not compile regex\n");
   return "Not Matched!";
  }

  ret = regexec(&regex, text, 0, NULL, 0);
  if (!ret) {
   regfree(&regex);
   return "Matched!";
  }
  regfree(&regex);
 }

 return "Not Matched!";
}