int * func0(int *numbers,int size,int delimiter,int *out_size)

{
  int *piVar1;
  int iVar2;
  int local_34;
  int j;
  int i;
  int *out;
  int *out_size_local;
  int delimiter_local;
  int size_local;
  int *numbers_local;
  
  if (size < 1) {
    local_34 = 0;
  }
  else {
    local_34 = size * 2 + -1;
  }
  *out_size = local_34;
  piVar1 = malloc((long)*out_size << 2);
  if (0 < size) {
    *piVar1 = *numbers;
  }
  j = 1;
  for (i = 1; i < size; i = i + 1) {
    iVar2 = j + 1;
    piVar1[j] = delimiter;
    j = j + 2;
    piVar1[iVar2] = numbers[i];
  }
  return piVar1;
}