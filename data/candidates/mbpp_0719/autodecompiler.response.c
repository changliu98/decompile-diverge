char *func0(char *string)
{
 int reti;
 char *pattern = "ab*?";
 regex_t regex;
 char *result;

 reti = regcomp(&regex, pattern, 1);
 if (reti) {
  result = "Regex compilation failed";
  goto out;
 }

 reti = regexec(&regex, string, 0, NULL, 0);
 regfree(&regex);

 if (!reti)
  result = "Found a match!";
 else
  result = "Not matched!";

out:
 return result;
}