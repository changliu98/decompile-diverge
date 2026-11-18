int func0(float *lst,int size)

{
  double dVar1;
  double dVar2;
  int i;
  int sum;
  int size_local;
  float *lst_local;
  
  sum = 0;
  for (i = 0; i < size; i = i + 1) {
    dVar1 = ceil((double)lst[i]);
    dVar2 = ceil((double)lst[i]);
    sum = (int)dVar1 * (int)dVar2 + sum;
  }
  return sum;
}