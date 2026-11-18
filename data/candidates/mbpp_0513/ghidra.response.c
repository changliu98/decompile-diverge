char ** func0(int *test_tup,int size,char *K)

{
  char **ppcVar1;
  int iVar2;
  int i;
  int j;
  char **res;
  char *K_local;
  int size_local;
  int *test_tup_local;
  
  ppcVar1 = malloc((long)(size << 1) << 3);
  j = 0;
  for (i = 0; i < size; i = i + 1) {
    iVar2 = j + 1;
    asprintf(ppcVar1 + j,"%d",(ulong)(uint)test_tup[i]);
    j = j + 2;
    ppcVar1[iVar2] = K;
  }
  return ppcVar1;
}