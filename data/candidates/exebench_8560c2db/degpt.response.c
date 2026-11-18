uint mc_bitcode(float *val,float thres)

{
  uint res;
  uint i;
  float thres_local;
  float *val_local;
  
  res = 0;
  for (i = 0; i < 8; i = i + 1) {
    if (thres < val[i]) {
      res = 1 << ((byte)i & 0x1f) | res;
    }
  }
  return res;
}