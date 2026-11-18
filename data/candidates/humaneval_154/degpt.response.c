_Bool func0(char *a,char *b)

{
  int iVar1;
  size_t sVar2;
  char *__dest;
  char *pcVar3;
  int i;
  char *temp;
  int len_b;
  int len_a;
  char *b_local;
  char *a_local;
  
  strlen(a);
  sVar2 = strlen(b);
  iVar1 = (int)sVar2;
  __dest = malloc((long)(iVar1 * 2 + 1));
  i = 0;
  while( true ) {
    if (iVar1 <= i) {
      free(__dest);
      return false;
    }
    strncpy(__dest,b + i,(long)(iVar1 - i));
    strncpy(__dest + ((long)iVar1 - (long)i),b,(long)i);
    __dest[iVar1] = '\0';
    pcVar3 = strstr(a,__dest);
    if (pcVar3 != (char *)0x0) break;
    i = i + 1;
  }
  free(__dest);
  return true;
}