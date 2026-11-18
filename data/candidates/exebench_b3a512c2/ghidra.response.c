int getPossibleCount(int *ptr,int *num)

{
  int count;
  int size;
  int i;
  int *num_local;
  int *ptr_local;
  
  count = 0;
  for (i = 0; i < 9; i = i + 1) {
    if ((ptr[i] != 0) && (count = count + 1, num != (int *)0x0)) {
      *num = ptr[i];
    }
  }
  return count;
}