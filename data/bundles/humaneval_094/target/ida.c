int __cdecl func0(int *lst, int size)
{
  int v3; // [rsp+0h] [rbp-2Ch]
  int j; // [rsp+4h] [rbp-28h]
  int prime; // [rsp+8h] [rbp-24h]
  int i; // [rsp+Ch] [rbp-20h]
  int num; // [rsp+14h] [rbp-18h]
  int sum; // [rsp+18h] [rbp-14h]
  int largest; // [rsp+1Ch] [rbp-10h]

  largest = 0;
  sum = 0;
  for ( i = 0; i < size; ++i )
  {
    num = lst[i];
    if ( num > 1 )
    {
      prime = 1;
      for ( j = 2; j * j <= num; ++j )
      {
        if ( !(num % j) )
        {
          prime = 0;
          break;
        }
      }
      if ( prime )
      {
        if ( num <= largest )
          v3 = largest;
        else
          v3 = lst[i];
        largest = v3;
      }
    }
  }
  while ( largest > 0 )
  {
    sum += largest % 10;
    largest /= 10;
  }
  return sum;
}