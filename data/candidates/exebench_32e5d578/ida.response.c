void __cdecl intToBin(unsigned int n, int *binary)
{
  int i; // [rsp+0h] [rbp-18h]

  for ( i = 0; i < 8; ++i )
  {
    binary[i] = (n & 0x80) != 0;
    n *= 2;
  }
}