int func0(int *li,int size,int min,int max)

{
  int i;
  int ctr;
  int max_local;
  int min_local;
  int size_local;
  int *li_local;
  
  ctr = 0;
  for (i = 0; i < size; i = i + 1) {
    if ((min <= li[i]) && (li[i] <= max)) {
      ctr = ctr + 1;
    }
  }
  return ctr;
}