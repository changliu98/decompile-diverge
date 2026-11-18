unsigned_long div10quickm(unsigned_long *tp)

{
  ulong uVar1;
  ulong uVar2;
  unsigned_long uVar3;
  unsigned_long t;
  unsigned_long r;
  unsigned_long q;
  unsigned_long *tp_local;
  
  uVar1 = *tp;
  uVar2 = (uVar1 >> 1) + (uVar1 >> 2);
  uVar2 = uVar2 + (uVar2 >> 4);
  uVar2 = uVar2 + (uVar2 >> 8);
  uVar2 = uVar2 + (uVar2 >> 0x10) >> 3;
  uVar3 = uVar2 + (uVar1 + uVar2 * -10 >> 9);
  *tp = uVar3;
  return *tp + uVar3 * -10;
}