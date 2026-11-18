void func0(int *arr,int n)

{
  int iVar1;
  int temp_1;
  int temp;
  int high;
  int mid;
  int low;
  int n_local;
  int *arr_local;
  
  low = 0;
  mid = 0;
  high = n + -1;
  while (mid <= high) {
    if (arr[mid] == 0) {
      iVar1 = arr[low];
      arr[low] = arr[mid];
      arr[mid] = iVar1;
      low = low + 1;
      mid = mid + 1;
    }
    else if (arr[mid] == 1) {
      mid = mid + 1;
    }
    else {
      iVar1 = arr[mid];
      arr[mid] = arr[high];
      arr[high] = iVar1;
      high = high + -1;
    }
  }
  return;
}