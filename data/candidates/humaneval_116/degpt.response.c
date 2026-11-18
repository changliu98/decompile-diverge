void func0(int *arr,int size)

{
  int iVar1;
  int j;
  int i;
  int temp;
  int y;
  int x;
  int count_ones;
  int size_local;
  int *arr_local;
  
  for (i = 0; j = i, i < size; i = i + 1) {
    while (j = j + 1, j < size) {
      count_ones = 0;
      y = arr[j];
      for (x = arr[i]; iVar1 = count_ones, 0 < x; x = x >> 1) {
        count_ones = (x & 1U) + count_ones;
      }
      count_ones = 0;
      for (; 0 < y; y = y >> 1) {
        count_ones = (y & 1U) + count_ones;
      }
      if ((count_ones < iVar1) || ((count_ones == iVar1 && (arr[j] < arr[i])))) {
        iVar1 = arr[i];
        arr[i] = arr[j];
        arr[j] = iVar1;
      }
    }
  }
  return;
}