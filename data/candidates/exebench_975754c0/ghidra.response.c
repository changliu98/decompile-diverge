void reverse(char *s)

{
  char cVar1;
  int iVar2;
  char c;
  int max;
  int i;
  char *s_local;
  
  for (i = 0; iVar2 = i, s[i] != '\0'; i = i + 1) {
  }
  for (i = 0; i < iVar2 / 2; i = i + 1) {
    cVar1 = s[i];
    s[i] = s[iVar2 - (i + 1)];
    s[iVar2 - (i + 1)] = cVar1;
  }
  return;
}