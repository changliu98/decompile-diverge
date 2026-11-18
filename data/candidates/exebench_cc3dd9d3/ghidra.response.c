void AssignBit(unsigned_long *array,int bit,int value)

{
  ulong uVar1;
  unsigned_long mask;
  int value_local;
  int bit_local;
  unsigned_long *array_local;
  
  uVar1 = 1L << ((byte)bit & 0x3f);
  if (value == 0) {
    array[(ulong)(long)bit >> 6] = (uVar1 ^ 0xffffffffffffffff) & array[(ulong)(long)bit >> 6];
  }
  else {
    array[(ulong)(long)bit >> 6] = uVar1 | array[(ulong)(long)bit >> 6];
  }
  return;
}