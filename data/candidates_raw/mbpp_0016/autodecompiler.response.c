char *check_name(char *str)
{
 char *pattern = "^[a-z]+_[a-z]+$";
 regex_t re;
 int reti;
 char *msg;

 regcomp(&re, pattern, 1);

 reti = regexec(&re, str, 0, NULL, 0);
 regfree(&re);

 if( !reti ){
  msg = "Found a match!";
 }else if( reti == REG_NOMATCH ){
  msg = "Not matched!";
 }else{
  msg = "Error!";
 }

 return msg;
}