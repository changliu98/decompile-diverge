char * pat_strcpy(char *s1,char *s2)

{
  char cVar1;
  char *pcVar2;
  char *s2_local;
  char *s1_local;
  
  s2_local = s2;
  pcVar2 = s1;
  do {
    s1_local = pcVar2;
    cVar1 = *s2_local;
    *s1_local = cVar1;
    s2_local = s2_local + 1;
    pcVar2 = s1_local + 1;
  } while (cVar1 != '\0');
  return s1_local;
}