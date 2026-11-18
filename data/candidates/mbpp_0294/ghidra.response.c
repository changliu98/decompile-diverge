int func0(int *listval,int size)

{
  int i;
  int max_val;
  int size_local;
  int *listval_local;
  
  max_val = -0x80000000;
  for (i = 0; i < size; i = i + 1) {
    if (max_val < listval[i]) {
      max_val = listval[i];
    }
  }
  return max_val;
}