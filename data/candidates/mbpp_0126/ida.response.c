int __cdecl func0(int a, int b)
{
  int v3; // [rsp+0h] [rbp-18h]
  int i; // [rsp+8h] [rbp-10h]
  int sum; // [rsp+Ch] [rbp-Ch]

  sum = 0;
  for ( i = 1; ; ++i )
  {
    v3 = a >= b ? b : a;
    if ( i >= v3 )
      break;
    if ( !(a % i) && !(b % i) )
      sum += i;
  }
  return sum;
}