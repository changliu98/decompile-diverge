int func0(int *arr,int n)

{
  int i;
  int sum;
  int n_local;
  int *arr_local;
  
  sum = 0;
  i = n;
  while (i = i + -1, -1 < i) {
    sum = (i * arr[i] - ((n + -1) - i) * arr[i]) + sum;
  }
  return sum;
}