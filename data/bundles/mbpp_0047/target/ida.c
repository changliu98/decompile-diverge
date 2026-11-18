int __cdecl func0(int A, int B)
{
  int i; // [rsp+4h] [rbp-14h]
  int variable; // [rsp+8h] [rbp-10h]

  variable = 1;
  if ( A == B )
    return 1;
  if ( B - A >= 5 )
    return 0;
  for ( i = A + 1; i <= B; ++i )
    variable = i % 10 * variable % 10;
  return variable % 10;
}