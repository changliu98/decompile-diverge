void __cdecl zeroTryte(int *tryte)
{
  int i; // [rsp+0h] [rbp-Ch]

  for ( i = 0; i < 6; ++i )
    tryte[i] = 0;
}