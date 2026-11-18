_Bool func0(int *arr,int n)

{
  bool bVar1;
  int i;
  int g;
  int n_local;
  int *arr_local;
  
  bVar1 = false;
  i = 1;
  while( true ) {
    if (n <= i) {
      return true;
    }
    if ((0 < arr[i] - arr[i + -1]) && (bVar1)) break;
    if (arr[i] - arr[i] < 0) {
      bVar1 = true;
    }
    i = i + 1;
  }
  return false;
}