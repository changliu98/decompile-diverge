void zeroTryte(int *tryte)

{
  int i;
  int *tryte_local;
  
  for (i = 0; i < 6; i = i + 1) {
    tryte[i] = 0;
  }
  return;
}