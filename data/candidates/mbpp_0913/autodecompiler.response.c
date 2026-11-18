int func0(char *str)
{
 regex_t regex;
 int reti;
 char buff[256];
 char match_found;

 regcomp(&regex,".*[0-9]$",0);

 reti = regexec(&regex,str,0,0,0);
 match_found = !reti;

 regfree(&regex);

 return match_found;
}