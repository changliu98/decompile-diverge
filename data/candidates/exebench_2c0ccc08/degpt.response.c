char * strcpy2(char *s,char *t)

{
  char cVar1;
  char *tmp;
  char *t_local;
  char *s_local;
  
  t_local = t;
  s_local = s;
  do {
    cVar1 = *t_local;
    *s_local = cVar1;
    t_local = t_local + 1;
    s_local = s_local + 1;
  } while (cVar1 != '\0');
  return s;
}