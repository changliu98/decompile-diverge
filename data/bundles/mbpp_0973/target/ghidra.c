char * func0(char *s,int d)

{
  int iVar1;
  size_t sVar2;
  char *pcVar3;
  int i;
  char *tmp;
  int len;
  int d_local;
  char *s_local;
  
  sVar2 = strlen(s);
  iVar1 = (int)sVar2;
  pcVar3 = malloc((long)(iVar1 + 1));
  for (i = 0; i < iVar1; i = i + 1) {
    pcVar3[i] = s[(i + d) % iVar1];
  }
  pcVar3[iVar1] = '\0';
  return pcVar3;
}