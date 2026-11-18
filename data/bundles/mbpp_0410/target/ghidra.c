int func0(char **listval,int size)

{
  int iVar1;
  int i;
  int current_val;
  int min_val;
  int size_local;
  char **listval_local;
  
  min_val = 0x7fffffff;
  size_local = size;
  listval_local = listval;
  for (i = 0; i < size_local; i = i + 1) {
    iVar1 = __isoc99_sscanf(listval_local[i],&DAT_00102004,&current_val);
    if ((iVar1 != 0) && (current_val < min_val)) {
      min_val = current_val;
    }
  }
  return min_val;
}