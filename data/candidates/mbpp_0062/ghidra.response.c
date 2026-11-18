int func0(int *xs,int size)

{
  int i;
  int min_val;
  int size_local;
  int *xs_local;
  
  min_val = 0x7fffffff;
  for (i = 0; i < size; i = i + 1) {
    if (xs[i] < min_val) {
      min_val = xs[i];
    }
  }
  return min_val;
}