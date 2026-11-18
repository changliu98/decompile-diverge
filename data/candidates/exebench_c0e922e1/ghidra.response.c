char * strcpy(char *destination,char *s)

{
  char *d;
  char *s_local;
  char *destination_local;
  
  d = destination;
  s_local = s;
  while (*s_local != '\0') {
    *d = *s_local;
    d = d + 1;
    s_local = s_local + 1;
  }
  *d = '\0';
  return destination;
}