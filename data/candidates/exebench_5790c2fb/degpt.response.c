void strcpy2(char *s,char *t)

{
  char cVar1;
  char *t_local;
  char *s_local;
  
  s_local = s;
  for (t_local = t; cVar1 = *t_local, *s_local = cVar1, cVar1 != '\0'; t_local = t_local + 1) {
    s_local = s_local + 1;
  }
  return;
}