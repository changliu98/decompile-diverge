void __cdecl int_to_str(unsigned int n, char *str)
{
  int i; // [rsp+0h] [rbp-14h]

  for ( i = 9; i >= 0; --i )
  {
    str[i] = n % 0xA + 48;
    n /= 0xAu;
  }
  str[10] = 0;
}