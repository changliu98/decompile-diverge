char *match(char *string)
{
 char *pattern = "[A-Z]+[a-z]+$";
 regex_t regex;
 int reti;
 char *result;

 regcomp(&regex, pattern, 1);

 reti = regexec(&regex, string, 0, NULL, 0);
 if( !reti ){
  result = "Found a match!";
 }
 else if( reti == REG_NOMATCH ){
  result = "Not matched!";
 }
 else{
  result = "Error!";
 }

 return result;
}