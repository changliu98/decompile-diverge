int func0(int *list,int size)

{
  int i;
  int res;
  int size_local;
  int *list_local;
  
  res = 0;
  for (i = 0; i < size; i = i + 1) {
    res = res * 10 + list[i];
  }
  return res;
}