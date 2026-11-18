void func0(int *arr,int arr_size,int k,int *out)

{
  int iVar1;
  int i_1;
  int temp;
  int j;
  int i;
  int *out_local;
  int k_local;
  int arr_size_local;
  int *arr_local;
  
  for (i = 0; i < arr_size + -1; i = i + 1) {
    for (j = 0; j < (arr_size - i) + -1; j = j + 1) {
      if (arr[j + 1] < arr[j]) {
        iVar1 = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = iVar1;
      }
    }
  }
  for (i_1 = 0; i_1 < k; i_1 = i_1 + 1) {
    out[i_1] = arr[(arr_size - k) + i_1];
  }
  return;
}