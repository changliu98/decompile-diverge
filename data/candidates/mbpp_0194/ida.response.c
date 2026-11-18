int __cdecl func0(int n)
{
  int last_digit; // [rsp+0h] [rbp-18h]
  int base; // [rsp+8h] [rbp-10h]
  int dec_value; // [rsp+Ch] [rbp-Ch]

  dec_value = 0;
  base = 1;
  while ( n )
  {
    last_digit = n % 10;
    n /= 10;
    dec_value += base * last_digit;
    base *= 8;
  }
  return dec_value;
}