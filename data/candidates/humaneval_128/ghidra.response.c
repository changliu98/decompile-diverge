int func0(int *arr,int arr_size)

{
  int iVar1;
  int i;
  int prods;
  int sum;
  int arr_size_local;
  int *arr_local;
  int local_c;
  
  if (arr_size == 0) {
    local_c = -0x8000;
  }
  else {
    sum = 0;
    prods = 1;
    for (i = 0; i < arr_size; i = i + 1) {
      iVar1 = abs(arr[i]);
      sum = iVar1 + sum;
      if (arr[i] == 0) {
        prods = 0;
      }
      if (arr[i] < 0) {
        prods = -prods;
      }
    }
    local_c = sum * prods;
  }
  return local_c;
}