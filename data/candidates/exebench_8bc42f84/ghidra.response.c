void mpeg3video_calc_mv(int *pred,int r_size,int motion_code,int motion_r,int full_pel_vector)

{
  int iVar1;
  byte bVar2;
  int local_30;
  int local_2c;
  int vec;
  int lim;
  int full_pel_vector_local;
  int motion_r_local;
  int motion_code_local;
  int r_size_local;
  int *pred_local;
  
  bVar2 = (byte)r_size;
  iVar1 = 0x10 << (bVar2 & 0x1f);
  if (full_pel_vector == 0) {
    local_2c = *pred;
  }
  else {
    local_2c = *pred >> 1;
  }
  vec = local_2c;
  if (motion_code < 1) {
    if ((motion_code < 0) &&
       (vec = local_2c - ((-1 - motion_code << (bVar2 & 0x1f)) + motion_r + 1), vec < -iVar1)) {
      vec = iVar1 * 2 + vec;
    }
  }
  else {
    vec = (motion_code + -1 << (bVar2 & 0x1f)) + motion_r + 1 + local_2c;
    if (iVar1 <= vec) {
      vec = vec + iVar1 * -2;
    }
  }
  if (full_pel_vector == 0) {
    local_30 = vec;
  }
  else {
    local_30 = vec << 1;
  }
  *pred = local_30;
  return;
}