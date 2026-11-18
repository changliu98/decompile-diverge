char * substitute(char *string,char chold,char chnew)

{
  char *cp;
  char chnew_local;
  char chold_local;
  char *string_local;
  
  cp = string;
  if (string != (char *)0x0) {
    for (; *cp != '\0'; cp = cp + 1) {
      if (*cp == chold) {
        *cp = chnew;
        return string;
      }
    }
  }
  return string;
}