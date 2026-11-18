int func0(char *s)

{
  int iVar1;
  size_t sVar2;
  char *pcVar3;
  int i;
  int length;
  int count;
  char *vowels;
  char *s_local;
  
  count = 0;
  sVar2 = strlen(s);
  iVar1 = (int)sVar2;
  for (i = 0; i < iVar1; i = i + 1) {
    pcVar3 = strchr("aeiouAEIOU",(int)s[i]);
    if (pcVar3 != (char *)0x0) {
      count = count + 1;
    }
  }
  if ((0 < iVar1) && ((s[iVar1 + -1] == 'y' || (s[iVar1 + -1] == 'Y')))) {
    count = count + 1;
  }
  return count;
}