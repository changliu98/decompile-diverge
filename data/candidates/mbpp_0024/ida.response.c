int __cdecl func0(int binary)
{
  int i; // [rsp+10h] [rbp-10h]
  int decimal; // [rsp+14h] [rbp-Ch]

  decimal = 0;
  i = 0;
  while ( binary )
  {
    decimal += (int)pow(2.0, (double)i) * (binary % 10);
    binary /= 10;
    ++i;
  }
  return decimal;
}