void func0(int *arr,int size,char ***out,int *out_size)

{
  int iVar1;
  bool bVar2;
  char **ppcVar3;
  int temp;
  int j;
  int i;
  char *names [10];
  int *out_size_local;
  char ***out_local;
  int size_local;
  int *arr_local;
  
  memcpy(names,&DAT_00103d90,0x50);
  for (i = 0; i < size + -1; i = i + 1) {
    for (j = 0; j < (size - i) + -1; j = j + 1) {
      if (arr[j + 1] < arr[j]) {
        iVar1 = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = iVar1;
      }
    }
  }
  *out_size = 0;
  i = size;
  while (i = i + -1, -1 < i) {
    if ((0 < arr[i]) && (arr[i] < 10)) {
      *out_size = *out_size + 1;
    }
  }
  ppcVar3 = malloc((long)*out_size << 3);
  *out = ppcVar3;
  j = 0;
  while( true ) {
    i = size + -1;
    bVar2 = false;
    if (-1 < i) {
      bVar2 = j < *out_size;
    }
    if (!bVar2) break;
    size = i;
    if ((0 < arr[i]) && (arr[i] < 10)) {
      (*out)[j] = names[arr[i]];
      j = j + 1;
    }
  }
  return;
}