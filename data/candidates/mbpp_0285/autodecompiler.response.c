char *func0(char *string)
{
 char *pattern = "ab{2,3}";
 regex_t reg;
 int reti;
 char *result;

 regcomp(&reg, pattern, 1);

 reti = regexec(&reg, string, 0, NULL, 0);
 if( !reti ){
  result = "Found a match!";
 }
 else if( reti == REG_NOMATCH ){
  result = "Not matched!";
 }
 else{
  result = "Error!";
 }

 regfree(&reg);

 return result;
}