int func0(int *arr,int n)

{
  int i;
  int XOR;
  int n_local;
  int *arr_local;
  
  XOR = 0;
  for (i = 0; i < n; i = i + 1) {
    XOR = XOR ^ arr[i];
  }
  return XOR;
}