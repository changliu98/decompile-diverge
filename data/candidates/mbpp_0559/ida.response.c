int __cdecl func0(int *a, int size)
{
  int i; // [rsp+0h] [rbp-18h]
  int max_ending_here; // [rsp+4h] [rbp-14h]
  int max_so_far; // [rsp+8h] [rbp-10h]

  max_so_far = 0;
  max_ending_here = 0;
  for ( i = 0; i < size; ++i )
  {
    max_ending_here += a[i];
    if ( max_ending_here >= 0 )
    {
      if ( max_so_far < max_ending_here )
        max_so_far = max_ending_here;
    }
    else
    {
      max_ending_here = 0;
    }
  }
  return max_so_far;
}