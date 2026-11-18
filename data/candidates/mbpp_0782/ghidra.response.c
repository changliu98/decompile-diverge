int func0(int *arr,int l)

{
  int i;
  int Sum;
  int l_local;
  int *arr_local;
  
  Sum = 0;
  for (i = 0; i < l; i = i + 1) {
    Sum = (((i + 1) * (l - i) + 1) / 2) * arr[i] + Sum;
  }
  return Sum;
}