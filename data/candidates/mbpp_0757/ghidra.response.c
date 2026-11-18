char * func0(char **test_list,int size)

{
  int iVar1;
  size_t sVar2;
  int i;
  int len;
  char reversed [100];
  int idxn;
  int idx;
  int count;
  int size_local;
  char **test_list_local;
  
  count = 0;
  for (idx = 0; idx < size; idx = idx + 1) {
    for (idxn = idx; idxn < size; idxn = idxn + 1) {
      sVar2 = strlen(test_list[idx]);
      iVar1 = (int)sVar2;
      for (i = 0; i < iVar1; i = i + 1) {
        reversed[i] = test_list[idx][(iVar1 + -1) - i];
      }
      reversed[iVar1] = '\0';
      iVar1 = strcmp(test_list[idxn],reversed);
      if (iVar1 == 0) {
        count = count + 1;
      }
    }
  }
  sprintf(func0::result,"%d",(ulong)(uint)count);
  return func0::result;
}