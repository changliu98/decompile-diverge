void func0(int *arr,int length)

{
  int iVar1;
  int temp;
  int end;
  int length_local;
  int *arr_local;
  
  heapify(arr,length);
  end = length + -1;
  while (0 < end) {
    iVar1 = arr[end];
    arr[end] = *arr;
    *arr = iVar1;
    end = end + -1;
    shift_down(arr,0,end);
  }
  return;
}