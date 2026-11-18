int obdRevConvert_31(float val,uint *A,uint *B,uint *C,uint *D)

{
  uint *D_local;
  uint *C_local;
  uint *B_local;
  uint *A_local;
  float val_local;
  
  *A = (uint)((long)val / 0x100);
  *B = (uint)((long)val % 0x100);
  return 2;
}