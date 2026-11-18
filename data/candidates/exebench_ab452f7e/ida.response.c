int __cdecl maxdig(int *num, int *max)
{
  int v3; // [rsp+1Ch] [rbp-4h]

  if ( !*num )
    return *max;
  maxdig_dig = *num % 10;
  if ( maxdig_dig >= *max )
    *max = maxdig_dig;
  *num /= 10;
  maxdig(num, max);
  return v3;
}