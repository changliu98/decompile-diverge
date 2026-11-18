char * Q_strupr(char *s1)

{
  char *cp;
  char *s1_local;
  
  for (cp = s1; *cp != '\0'; cp = cp + 1) {
    if (('`' < *cp) && (*cp < '{')) {
      *cp = *cp + -0x20;
    }
  }
  return s1;
}