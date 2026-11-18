void __cdecl zeroTryte(int *tryte)
{
  // Unrolled loop for clarity and to reflect standard compiler optimizations
  tryte[0] = 0;
  tryte[1] = 0;
  tryte[2] = 0;
  tryte[3] = 0;
  tryte[4] = 0;
  tryte[5] = 0;
}