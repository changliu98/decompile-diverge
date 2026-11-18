char *func0(char *str)
{
 regex_t regex;
 int ret;
 char *result;

 ret = regcomp(&regex, "ab+", 1);
 if (ret) {
  result = "Regex compilation failed!";
  goto out;
 }

 ret = regexec(&regex, str, 0, NULL, 0);
 regfree(&regex);

 if (!ret)
  result = "Found a match!";
 else
  result = "Not matched!";

out:
 return result;
}