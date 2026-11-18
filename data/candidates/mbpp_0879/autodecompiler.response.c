char *func0(char *string)
{
 regex_t regex;
 int reti;
 char *ret_str;

 char *pattern = "a.*?b$";
 reti = regcomp(&regex, pattern, 1);
 if( reti ) {
  ret_str = "Regex compilation failed.";
  goto out;
 }

 reti = regexec(&regex, string, 0, NULL, 0);
 if( !reti ) {
  ret_str = "Found a match!";
 } else if( reti == 1 ) {
  ret_str = "Not matched!";
 } else {
  ret_str = "Regex match failed.";
 }
out:
 return ret_str;
}