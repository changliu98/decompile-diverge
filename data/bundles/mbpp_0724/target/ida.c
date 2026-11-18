int __cdecl func0(int base, int power)
{
  int i_0; // [rsp+0h] [rbp-FD0h]
  int sum; // [rsp+4h] [rbp-FCCh]
  long temp; // [rsp+8h] [rbp-FC8h]
  int i; // [rsp+10h] [rbp-FC0h]
  int carry; // [rsp+14h] [rbp-FBCh]
  int p; // [rsp+18h] [rbp-FB8h]
  int size; // [rsp+1Ch] [rbp-FB4h]
  int digits[1000]; // [rsp+20h] [rbp-FB0h]
  int powera; // [rsp+FC8h] [rbp-8h]
  int basea; // [rsp+FCCh] [rbp-4h]

  basea = base;
  powera = power;
  size = 1;
  digits[0] = 1;
  for ( p = 0; p < powera; ++p )
  {
    carry = 0;
    for ( i = 0; i < size; ++i )
    {
      temp = carry + basea * (__int64)digits[i];
      digits[i] = temp % 10;
      carry = temp / 10;
    }
    while ( carry > 0 )
    {
      digits[size] = carry % 10;
      carry /= 10;
      ++size;
    }
  }
  sum = 0;
  for ( i_0 = 0; i_0 < size; ++i_0 )
    sum += digits[i_0];
  return sum;
}