int __cdecl factors(int M, int *arr)
{
  int m2; // [rsp+0h] [rbp-28h]
  int m1; // [rsp+4h] [rbp-24h]
  int num; // [rsp+Ch] [rbp-1Ch]
  int i; // [rsp+14h] [rbp-14h]

  i = 0;
  while ( !(M % 53) )
  {
    M /= 53;
    arr[i++] = 53;
  }
  while ( !(M % 47) )
  {
    M /= 47;
    arr[i++] = 47;
  }
  while ( !(M % 43) )
  {
    M /= 43;
    arr[i++] = 43;
  }
  while ( !(M % 41) )
  {
    M /= 41;
    arr[i++] = 41;
  }
  while ( !(M % 37) )
  {
    M /= 37;
    arr[i++] = 37;
  }
  while ( !(M % 31) )
  {
    M /= 31;
    arr[i++] = 31;
  }
  while ( !(M % 29) )
  {
    M /= 29;
    arr[i++] = 29;
  }
  while ( !(M % 23) )
  {
    M /= 23;
    arr[i++] = 23;
  }
  while ( !(M % 19) )
  {
    M /= 19;
    arr[i++] = 19;
  }
  while ( !(M % 17) )
  {
    M /= 17;
    arr[i++] = 17;
  }
  while ( !(M % 13) )
  {
    M /= 13;
    arr[i++] = 13;
  }
  while ( !(M % 11) )
  {
    M /= 11;
    arr[i++] = 11;
  }
  while ( !(M % 8) )
  {
    M /= 8;
    arr[i++] = 8;
  }
  while ( !(M % 7) )
  {
    M /= 7;
    arr[i++] = 7;
  }
  while ( !(M % 5) )
  {
    M /= 5;
    arr[i++] = 5;
  }
  while ( !(M % 4) )
  {
    M /= 4;
    arr[i++] = 4;
  }
  while ( !(M % 3) )
  {
    M /= 3;
    arr[i++] = 3;
  }
  while ( !(M % 2) )
  {
    M /= 2;
    arr[i++] = 2;
  }
  if ( M > 31 )
  {
    num = 2;
    while ( M > 1 )
    {
      m1 = 6 * num - 1;
      m2 = 6 * num + 1;
      while ( !(M % m1) )
      {
        arr[i++] = m1;
        M /= m1;
      }
      while ( !(M % m2) )
      {
        arr[i++] = m2;
        M /= m2;
      }
      ++num;
    }
  }
  return i;
}