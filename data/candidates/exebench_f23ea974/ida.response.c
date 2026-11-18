void __cdecl array_are_reference_type(int *arr)
{
  int tmp; // [rsp+0h] [rbp-Ch]

  tmp = *arr;
  *arr = arr[1];
  arr[1] = tmp;
}