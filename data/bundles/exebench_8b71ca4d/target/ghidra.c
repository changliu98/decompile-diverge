char * strcpy(char *s1,char *s2)

{
  long lVar1;
  int i;
  char *s2_local;
  char *s1_local;
  
  i = 0;
  do {
    s1[i] = s2[i];
    lVar1 = (long)i;
    i = i + 1;
  } while (s2[lVar1] != '\0');
  return s1;
}