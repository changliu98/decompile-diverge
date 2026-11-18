int find_max_idx(float *f)

{
  int i;
  int idx;
  float en;
  float *f_local;
  int local_c;
  
  en = 0.0;
  idx = -1;
  for (i = 0; i < 0x10; i = i + 1) {
    if (en < f[i]) {
      en = f[i];
      idx = i;
    }
  }
  if (idx < 0) {
    local_c = -1;
  }
  else {
    for (i = 0; i < 0x10; i = i + 1) {
      if ((idx != i) && ((float)((double)en * DAT_00102008) < f[i])) {
        return -1;
      }
    }
    local_c = idx;
  }
  return local_c;
}