char * GO_strcpy(char *d,char *s)

{
  char cVar1;
  char *tmp;
  char *s_local;
  char *d_local;
  
  s_local = s;
  d_local = d;
  do {
    cVar1 = *s_local;
    *d_local = cVar1;
    s_local = s_local + 1;
    d_local = d_local + 1;
  } while (cVar1 != '\0');
  return d;
}