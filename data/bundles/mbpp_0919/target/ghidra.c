int func0(int *items,int length)

{
  int i;
  int tot;
  int length_local;
  int *items_local;
  
  tot = 1;
  for (i = 0; i < length; i = i + 1) {
    tot = items[i] * tot;
  }
  return tot;
}