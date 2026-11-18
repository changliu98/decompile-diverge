void func0(int *arr,int len)

{
  int len_00;
  int *arr_00;
  int *arr_01;
  int i_1;
  int i;
  int *right;
  int *left;
  int mid;
  int len_local;
  int *arr_local;
  
  if (1 < len) {
    len_00 = len / 2;
    arr_00 = malloc((long)len_00 << 2);
    arr_01 = malloc((long)(len - len_00) << 2);
    for (i = 0; i_1 = len_00, i < len_00; i = i + 1) {
      arr_00[i] = arr[i];
    }
    for (; i_1 < len; i_1 = i_1 + 1) {
      arr_01[i_1 - len_00] = arr[i_1];
    }
    func0(arr_00,len_00);
    func0(arr_01,len - len_00);
    merge(arr_00,len_00,arr_01,len - len_00,arr);
    free(arr_00);
    free(arr_01);
  }
  return;
}