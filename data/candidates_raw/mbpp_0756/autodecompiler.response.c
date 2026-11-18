char *test_regcomp(char *string)
{
 int status;
 char *result;
 regex_t re;

 if ((status = regcomp(&re, "ab?", 1)) != 0) {
  result = "Not matched!";
 } else {
  if ((status = regexec(&re, string, 0, NULL, 0)) == 0) {
   result = "Found a match!";
  } else {
   result = "Not matched!";
  }
  regfree(&re);
 }

 return result;
}