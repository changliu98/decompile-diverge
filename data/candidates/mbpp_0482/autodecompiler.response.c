char* func0(char* input)
{
 char* pattern = "[A-Z]+[a-z]+$";
 regex_t regex;
 int reti;
 char* status;

 regcomp(&regex, pattern, 1);
 reti = regexec(&regex, input, 0, NULL, 0);

 regfree(&regex);

 if( !reti )
  status = "Yes";
 else
  status = "No";

 return status;
}