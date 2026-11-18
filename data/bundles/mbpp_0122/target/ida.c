int __cdecl func0(int n)
{
  int v1; // eax
  int temp; // [rsp+8h] [rbp-5DE8h]
  int j_0; // [rsp+Ch] [rbp-5DE4h]
  int i_0; // [rsp+10h] [rbp-5DE0h]
  int j; // [rsp+14h] [rbp-5DDCh]
  int i; // [rsp+18h] [rbp-5DD8h]
  int resultIndex; // [rsp+1Ch] [rbp-5DD4h]
  int result[3000]; // [rsp+20h] [rbp-5DD0h]
  int primes[3000]; // [rsp+2F00h] [rbp-2EF0h] BYREF
  int na; // [rsp+5DECh] [rbp-4h]

  na = n;
  memset(primes, 0, sizeof(primes));
  resultIndex = 0;
  for ( i = 2; i < 3000; ++i )
  {
    if ( !primes[i] )
    {
      primes[i] = 1;
      for ( j = 2 * i; j < 3000; j += i )
      {
        if ( --primes[j] == -3 )
        {
          v1 = resultIndex++;
          result[v1] = j;
        }
      }
    }
  }
  for ( i_0 = 0; i_0 < resultIndex - 1; ++i_0 )
  {
    for ( j_0 = 0; j_0 < resultIndex - i_0 - 1; ++j_0 )
    {
      if ( result[j_0] > result[j_0 + 1] )
      {
        temp = result[j_0];
        result[j_0] = result[j_0 + 1];
        result[j_0 + 1] = temp;
      }
    }
  }
  return result[na - 1];
}