void __cdecl func0(int *arr, int size, int number)
{
  int temp; // [rsp+4h] [rbp-1Ch]
  int j; // [rsp+8h] [rbp-18h]
  int i; // [rsp+Ch] [rbp-14h]

  for ( i = 0; i < size - 1; ++i )
  {
    for ( j = 0; j < size - i - 1; ++j )
    {
      if ( arr[j] > arr[j + 1] )
      {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
  if ( number <= arr[size - 1] )
    printf("No, entered number is less than those in the array\n");
  else
    printf("Yes, the entered number is greater than those in the array\n");
}