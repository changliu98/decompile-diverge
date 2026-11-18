void __cdecl func0(int *arr, int n)
{
  int temp_0; // [rsp+0h] [rbp-20h]
  int temp; // [rsp+4h] [rbp-1Ch]
  int high; // [rsp+8h] [rbp-18h]
  int mid; // [rsp+Ch] [rbp-14h]
  int low; // [rsp+10h] [rbp-10h]

  low = 0;
  mid = 0;
  high = n - 1;
  while ( mid <= high )
  {
    if ( arr[mid] )
    {
      if ( arr[mid] == 1 )
      {
        ++mid;
      }
      else
      {
        temp_0 = arr[mid];
        arr[mid] = arr[high];
        arr[high--] = temp_0;
      }
    }
    else
    {
      temp = arr[low];
      arr[low] = arr[mid];
      arr[mid] = temp;
      ++low;
      ++mid;
    }
  }
}