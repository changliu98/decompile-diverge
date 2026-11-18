char* func0(char* email)
{
 regex_t regex;
 int reti;
 reti = regcomp(&regex, "^[a-z0-9]+[\\._]?[a-z0-9]+[@]\\w+[.]\\w{2,3}$", 0x00000001 | 0x00000008);
 if(reti)
 {
  return "Invalid Email";
 }
 reti = regexec(&regex, email, 0, NULL, 0);
 regfree(&regex);
 if(!reti)
 {
  return "Valid Email";
 }
 else
 {
  return "Invalid Email";
 }
}