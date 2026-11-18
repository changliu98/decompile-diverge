void func0(int *l,int size)

{
  int i;
  int size_local;
  int *l_local;
  
  for (i = 0; i < size; i = i + 1) {
    l[i] = l[i] + 1;
  }
  return;
}