void __cdecl array_are_reference_type(int *arr)
{
  // Swap the first and second elements of the array
  int tmp = arr[0];
  arr[0] = arr[1];
  arr[1] = tmp;
}