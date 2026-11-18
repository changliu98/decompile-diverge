int obdRevConvert_04(float val,uint *A,uint *B,uint *C,uint *D)

{
  uint *D_local;
  uint *C_local;
  uint *B_local;
  uint *A_local;
  float val_local;
  
  *A = (uint)(long)((val * DAT_00102004) / DAT_00102008);
  return 1;
}