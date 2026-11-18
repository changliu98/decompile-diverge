char ** func0(char **lst,int lst_size,int *return_size)

{
  char *pcVar1;
  int iVar2;
  size_t sVar3;
  size_t sVar4;
  char **ppcVar5;
  char **out;
  size_t len_j1;
  size_t len_j;
  char *temp;
  int j;
  int i;
  int *return_size_local;
  int lst_size_local;
  char **lst_local;
  
  *return_size = 0;
  for (i = 0; i < lst_size; i = i + 1) {
    sVar3 = strlen(lst[i]);
    if ((sVar3 & 1) == 0) {
      lst[*return_size] = lst[i];
      *return_size = *return_size + 1;
    }
  }
  i = 0;
  do {
    if (*return_size + -1 <= i) {
      ppcVar5 = malloc((long)*return_size << 3);
      for (i = 0; i < *return_size; i = i + 1) {
        ppcVar5[i] = lst[i];
      }
      return ppcVar5;
    }
    for (j = 0; j < (*return_size - i) + -1; j = j + 1) {
      sVar3 = strlen(lst[j]);
      sVar4 = strlen(lst[j + 1]);
      if (sVar4 < sVar3) {
LAB_00101327:
        pcVar1 = lst[j];
        lst[j] = lst[j + 1];
        lst[j + 1] = pcVar1;
      }
      else if (sVar3 == sVar4) {
        iVar2 = strcmp(lst[j],lst[j + 1]);
        if (0 < iVar2) goto LAB_00101327;
      }
    }
    i = i + 1;
  } while( true );
}