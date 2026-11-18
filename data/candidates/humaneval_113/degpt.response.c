char ** func0(char **lst,int size)

{
  char **ppcVar1;
  char *pcVar2;
  int j;
  int sum;
  int i;
  char **out;
  int size_local;
  char **lst_local;
  
  ppcVar1 = malloc((long)size << 3);
  for (i = 0; i < size; i = i + 1) {
    sum = 0;
    for (j = 0; lst[i][j] != '\0'; j = j + 1) {
      if ((('/' < lst[i][j]) && (lst[i][j] < ':')) && ((lst[i][j] + -0x30) % 2 == 1)) {
        sum = sum + 1;
      }
    }
    pcVar2 = malloc(100);
    ppcVar1[i] = pcVar2;
    sprintf(ppcVar1[i],"the number of odd elements %d in the string %d of the %d input.",
            (ulong)(uint)sum,(ulong)(uint)sum,(ulong)(uint)sum);
  }
  return ppcVar1;
}