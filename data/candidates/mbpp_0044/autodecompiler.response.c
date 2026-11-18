char *func0(char *str)
{
 regex_t regex;
 int reti;
 char *ret_str;
 char *pattern = "^[[:alnum:]_]+";

 if (regcomp(&regex, pattern, 1)) {
  ret_str = "Regex compilation error";
  goto out;
 }

 reti = regexec(&regex, str, 0, NULL, 0);
 regfree(&regex);

 if (!reti)
  ret_str = "Found a match!";
 else
  ret_str = "Not matched!";

out:
 return ret_str;
}