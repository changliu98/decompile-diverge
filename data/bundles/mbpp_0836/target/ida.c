int __cdecl func0(int *a, int size)
{
  __int64 i; // [rsp+0h] [rbp-24h]
  __int64 end; // [rsp+8h] [rbp-1Ch]
  int max_ending_here; // [rsp+10h] [rbp-14h]
  int max_so_far; // [rsp+14h] [rbp-10h]

  max_so_far = 0x80000000;
  max_ending_here = 0;
  end = 0LL;
  for ( i = 0LL; (int)i < size; LODWORD(i) = i + 1 )
  {
    max_ending_here += a[(int)i];
    if ( max_so_far < max_ending_here )
    {
      max_so_far = max_ending_here;
      end = i;
    }
    if ( max_ending_here < 0 )
    {
      max_ending_here = 0;
      HIDWORD(i) = i + 1;
    }
  }
  return end - HIDWORD(end) + 1;
}