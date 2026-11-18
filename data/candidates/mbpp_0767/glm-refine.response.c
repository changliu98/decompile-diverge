int __cdecl count_pairs_with_sum(int *arr, int n, int target_sum)
{
  int j;
  int i;
  int count;

  count = 0;
  for ( i = 0; i < n; ++i )
  {
    for ( j = i + 1; j < n; ++j )
    {
      if ( arr[j] + arr[i] == target_sum )
        ++count;
    }
  }
  return count;
}