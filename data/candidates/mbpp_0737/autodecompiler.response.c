char *func0(char *str)
{
 char *pattern = "^[aeiouAEIOU][A-Za-z0-9_]*";
 regex_t regex;
 int reti;
 char *ret;
 regcomp(&regex, pattern, 9);
 reti = regexec(&regex, str, 0, NULL, 0);
 regfree(&regex);
 if(!(reti)) ret = "Valid";
 else ret = "Invalid";
 return ret;
}