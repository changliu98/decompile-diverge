bool __cdecl func0(int *set, int n, int sum)
{
  bool v4; // [rsp+7h] [rbp-19h]

  if ( !sum )
    return 1;
  if ( !n )
    return 0;
  if ( set[n - 1] > sum )
    return func0(set, n - 1, sum);
  v4 = 1;
  if ( !func0(set, n - 1, sum) )
    return func0(set, n - 1, sum - set[n - 1]);
  return v4;
}