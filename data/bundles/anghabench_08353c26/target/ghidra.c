int clip_f15(int v)

{
  int local_14;
  int local_10;
  int v_local;
  
  if (v < -0x7fff) {
    local_10 = -0x7fff;
  }
  else {
    local_14 = v;
    if (0x7fff < v) {
      local_14 = 0x7fff;
    }
    local_10 = local_14;
  }
  return local_10;
}