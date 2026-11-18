int func0(char *s)

{
  size_t sVar1;
  char *pcVar2;
  bool bVar3;
  int i;
  int count;
  char *uvowel;
  char *s_local;
  
  count = 0;
  i = 0;
  while( true ) {
    bVar3 = false;
    if (s[i] != '\0') {
      sVar1 = strlen(s);
      bVar3 = (ulong)(long)(i << 1) < sVar1;
    }
    if (!bVar3) break;
    pcVar2 = strchr("AEIOU",(int)s[i << 1]);
    if (pcVar2 != (char *)0x0) {
      count = count + 1;
    }
    i = i + 1;
  }
  return count;
}