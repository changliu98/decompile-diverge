int __cdecl func0(int n)
{
  int fctr; // [rsp+0h] [rbp-Ch]
  int fctrsum; // [rsp+4h] [rbp-8h]

  fctrsum = 0;
  for ( fctr = 1; fctr < n; ++fctr )
  {
    if ( !(n % fctr) )
      fctrsum += fctr;
  }
  return fctrsum > n;
}