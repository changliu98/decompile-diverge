int __cdecl maxdig(int *num, int *max)
{
  int v3;

  if ( !*num )
    return *max;
    
  maxdig_dig = *num % 10;
  if ( maxdig_dig >= *max )
    *max = maxdig_dig;
    
  *num /= 10;
  v3 = maxdig(num, max);
  
  return v3;
}