int func0(int *arr,int n)

{
  int i;
  int odd;
  int n_local;
  int *arr_local;
  int local_c;
  
  odd = 0;
  for (i = 0; i < n; i = i + 1) {
    if (arr[i] % 2 != 0) {
      odd = odd + 1;
    }
  }
  if (odd % 2 == 0) {
    local_c = 2;
  }
  else {
    local_c = 1;
  }
  return local_c;
}