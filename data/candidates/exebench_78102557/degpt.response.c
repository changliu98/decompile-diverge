char * strcpy(char *s1,char *s2)

{
  char cVar1;
  char *p;
  char *s2_local;
  char *s1_local;
  
  s2_local = s2;
  s1_local = s1;
  do {
    cVar1 = *s2_local;
    *s1_local = cVar1;
    s2_local = s2_local + 1;
    s1_local = s1_local + 1;
  } while (cVar1 != '\0');
  return s1;
}