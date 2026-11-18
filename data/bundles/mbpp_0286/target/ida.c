int __cdecl func0(int *a, int n, int k)
{
  int i; // [rsp+4h] [rbp-1Ch]
  int max_ending_here; // [rsp+8h] [rbp-18h]
  signed int max_so_far; // [rsp+Ch] [rbp-14h]

  max_so_far = 0x80000000;
  max_ending_here = 0;
  for ( i = 0; i < k * n; ++i )
  {
    max_ending_here += a[i % n];
    if ( max_so_far < max_ending_here )
      max_so_far = max_ending_here;
    if ( max_ending_here < 0 )
      max_ending_here = 0;
  }
  return max_so_far;
}