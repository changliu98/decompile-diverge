char * strcpy(char *dest,char *src)

{
  char cVar1;
  char *pcVar2;
  int d2;
  int d1;
  int d0;
  char *src_local;
  char *dest_local;
  
  pcVar2 = dest;
  do {
    cVar1 = *src;
    *pcVar2 = cVar1;
    src = src + 1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  return dest;
}