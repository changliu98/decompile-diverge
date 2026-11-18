/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

double readDummyArray(double *dummy,unsigned_long sizeMB)

{
  ulong uVar1;
  undefined1 auVar2 [16];
  double a;
  unsigned_long i;
  unsigned_long end;
  unsigned_long sizeMB_local;
  double *dummy_local;
  
  uVar1 = sizeMB >> 3;
  a = 0.0;
  for (i = 0; i < uVar1; i = i + 1) {
    a = dummy[i] + a;
  }
  auVar2._8_4_ = (uint)(sizeMB >> 0x23);
  auVar2._0_8_ = uVar1;
  auVar2._12_4_ = _UNK_00102014;
  *dummy = a / ((auVar2._8_8_ - _UNK_00102028) +
               ((double)CONCAT44(_DAT_00102010,(int)uVar1) - _DAT_00102020));
  return a;
}