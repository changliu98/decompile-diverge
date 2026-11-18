void __cdecl func0(int *arr, int n)
{
  int index; // [rsp+Ch] [rbp-14h]
  int out_of_place; // [rsp+10h] [rbp-10h]

  out_of_place = -1;
  for ( index = 0; index < n; ++index )
  {
    if ( out_of_place >= 0 && (arr[index] >= 0 && arr[out_of_place] < 0 || arr[index] < 0 && arr[out_of_place] >= 0) )
    {
      right_rotate(arr, n, out_of_place, index);
      if ( index - out_of_place <= 2 )
        out_of_place = -1;
      else
        out_of_place += 2;
    }
    if ( out_of_place == -1 && (arr[index] >= 0 && !(index % 2) || arr[index] < 0 && index % 2 == 1) )
      out_of_place = index;
  }
}