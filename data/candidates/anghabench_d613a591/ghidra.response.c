float _RGB(float H,float M1,float M2)

{
  float M2_local;
  float M1_local;
  float H_local;
  float local_c;
  
  if (0.0 <= H) {
    H_local = H;
    if (DAT_00102008 < (double)H) {
      H_local = (float)((double)H - DAT_00102008);
    }
  }
  else {
    H_local = (float)((double)H + DAT_00102008);
  }
  if (DAT_00102030 <= H_local) {
    if ((((H_local < DAT_00102030) || (local_c = M2, DAT_00102034 <= H_local)) &&
        (local_c = M1, DAT_00102034 <= H_local)) && (H_local < DAT_00102038)) {
      local_c = (float)((double)M1 + (double)((M2 - M1) * (DAT_00102038 - H_local)) / DAT_00102010);
    }
  }
  else {
    local_c = (float)((double)M1 + (double)((M2 - M1) * H_local) / DAT_00102010);
  }
  return local_c;
}