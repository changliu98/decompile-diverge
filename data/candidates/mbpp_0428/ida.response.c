void __cdecl func0(int *my_list, int length)
{
  bool v2; // [rsp+1h] [rbp-1Dh]
  int j; // [rsp+2h] [rbp-1Ch]
  int current_item; // [rsp+6h] [rbp-18h]
  int i; // [rsp+Ah] [rbp-14h]
  int gap; // [rsp+Eh] [rbp-10h]

  for ( gap = length / 2; gap > 0; gap /= 2 )
  {
    for ( i = gap; i < length; ++i )
    {
      current_item = my_list[i];
      for ( j = i; ; j -= gap )
      {
        v2 = 0;
        if ( j >= gap )
          v2 = my_list[j - gap] > current_item;
        if ( !v2 )
          break;
        my_list[j] = my_list[j - gap];
      }
      my_list[j] = current_item;
    }
  }
}