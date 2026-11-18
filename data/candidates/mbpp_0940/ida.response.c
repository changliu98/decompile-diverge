void __cdecl func0(int *arr, int length)
{
  int temp; // [rsp+Ch] [rbp-14h]
  int end; // [rsp+10h] [rbp-10h]

  heapify(arr, length);
  for ( end = length - 1; end > 0; shift_down(arr, 0, end) )
  {
    temp = arr[end];
    arr[end] = *arr;
    *arr = temp;
    --end;
  }
}