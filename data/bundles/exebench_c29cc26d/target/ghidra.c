char * strcpy_x86_64_fast(char *s1,char *s2)

{
  char cVar1;
  char *pcVar2;
  int rdst;
  int rsrc;
  char *s2_local;
  char *s1_local;
  
  pcVar2 = s1;
  do {
    cVar1 = *s2;
    *pcVar2 = cVar1;
    s2 = s2 + 1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  return s1;
}