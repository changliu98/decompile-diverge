int func0(int *arr,int n)

{
  int iVar1;
  int diff;
  int temp;
  int j;
  int i;
  int n_local;
  int *arr_local;
  
  for (i = 0; i < n + -1; i = i + 1) {
    for (j = 0; j < (n - i) + -1; j = j + 1) {
      if (arr[j + 1] < arr[j]) {
        iVar1 = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = iVar1;
      }
    }
  }
  diff = 0x7fffffff;
  for (i = 0; i < n + -1; i = i + 1) {
    if (arr[i + 1] - arr[i] < diff) {
      diff = arr[i + 1] - arr[i];
    }
  }
  return diff;
}