char *func0(char *string, char *pattern)
{
 regex_t regex;
 int reti;
 char *message;

 reti = regcomp(&regex, pattern, 0);
 if( reti )
 {
  message = "Regex compilation failed!";
  return message;
 }

 reti = regexec(&regex, string, 0, NULL, 0);
 regfree(&regex);

 if( !reti )
 {
  message = "Matched!";
 }
 else if( reti == REG_NOMATCH )
 {
  message = "No match";
 }
 else
 {
  message = "Regex match failed!";
 }

 return message;
}