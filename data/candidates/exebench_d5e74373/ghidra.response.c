int obdRevConvert_3C_3F(float val,uint *A,uint *B,uint *C,uint *D)

{
  float fVar1;
  uint *D_local;
  uint *C_local;
  uint *B_local;
  uint *A_local;
  float val_local;
  
  fVar1 = DAT_00102004 * (DAT_00102008 + val);
  *A = (uint)((long)fVar1 / 0x100);
  *B = (uint)((long)fVar1 % 0x100);
  return 2;
}