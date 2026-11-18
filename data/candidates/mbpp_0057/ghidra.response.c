int func0(int *arr,int n)

{
  int iVar1;
  int i_1;
  int num;
  int temp;
  int j;
  int i;
  int n_local;
  int *arr_local;
  
  for (i = 0; j = i, i < n + -1; i = i + 1) {
    while (j = j + 1, j < n) {
      if (arr[i] < arr[j]) {
        iVar1 = arr[i];
        arr[i] = arr[j];
        arr[j] = iVar1;
      }
    }
  }
  num = *arr;
  for (i_1 = 1; i_1 < n; i_1 = i_1 + 1) {
    num = num * 10 + arr[i_1];
  }
  return num;
}