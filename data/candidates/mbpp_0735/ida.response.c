int __cdecl func0(int n)
{
  if ( n == 1 )
    return 1;
  else
    return set_middle_bits(n) ^ n;
}