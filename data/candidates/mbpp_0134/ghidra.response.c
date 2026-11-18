char * func0(int *arr,int n,int p)

{
  int i;
  int _sum;
  int p_local;
  int n_local;
  int *arr_local;
  char *local_10;
  
  _sum = 0;
  for (i = 0; i < n; i = i + 1) {
    _sum = arr[i] + _sum;
  }
  if (p == 1) {
    if (_sum % 2 == 0) {
      local_10 = "ODD";
    }
    else {
      local_10 = "EVEN";
    }
  }
  else {
    local_10 = "EVEN";
  }
  return local_10;
}