char *test_regex(char *string)
{
 char *pattern = "\\w+\\S*$";
 regex_t regex;
 regmatch_t matches[1];
 char *result;

 if (!regcomp(&regex, pattern, 1)) {
  if (!regexec(&regex, string, 1, matches, 0)) {
   regfree(&regex);
   result = "Found a match!";
  } else {
   regfree(&regex);
   result = "Not matched!";
  }
 } else {
  result = "Regex compilation failed";
 }

 return result;
}