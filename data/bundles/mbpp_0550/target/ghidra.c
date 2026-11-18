int func0(int *arr,int low,int high)

{
  int iVar1;
  int mid;
  int high_local;
  int low_local;
  int *arr_local;
  int local_c;
  
  if (high < low) {
    local_c = *arr;
  }
  else if (high == low) {
    local_c = arr[low];
  }
  else {
    iVar1 = low + (high - low) / 2;
    if ((iVar1 < high) && (arr[iVar1 + 1] < arr[iVar1])) {
      local_c = arr[iVar1];
    }
    else if ((low < iVar1) && (arr[iVar1] < arr[iVar1 + -1])) {
      local_c = arr[iVar1 + -1];
    }
    else if (arr[iVar1] < arr[low]) {
      local_c = func0(arr,low,iVar1 + -1);
    }
    else {
      local_c = func0(arr,iVar1 + 1,high);
    }
  }
  return local_c;
}