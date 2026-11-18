char ** func0(char *str,int *count)

{
  int iVar1;
  size_t sVar2;
  char **ppcVar3;
  char *pcVar4;
  size_t current_len;
  int i;
  char *current;
  char **out;
  int len;
  int *count_local;
  char *str_local;
  
  sVar2 = strlen(str);
  iVar1 = (int)sVar2;
  ppcVar3 = malloc((long)iVar1 << 3);
  current = malloc((long)(iVar1 + 1));
  *current = '\0';
  for (i = 0; i < iVar1; i = i + 1) {
    sVar2 = strlen(current);
    current = realloc(current,sVar2 + 2);
    current[sVar2] = str[i];
    current[sVar2 + 1] = '\0';
    sVar2 = strlen(current);
    pcVar4 = malloc(sVar2 + 1);
    ppcVar3[i] = pcVar4;
    strcpy(ppcVar3[i],current);
  }
  free(current);
  *count = iVar1;
  return ppcVar3;
}