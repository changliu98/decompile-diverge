void od_filter_dering_direction_offsets(int *offset,int dir,int bstride)

{
  int f;
  int k;
  int bstride_local;
  int dir_local;
  int *offset_local;
  
  if (dir < 5) {
    for (k = 1; k < 4; k = k + 1) {
      offset[k + -1] = (((dir + -2) * k) / 2) * bstride + k;
    }
  }
  else {
    for (k = 1; k < 4; k = k + 1) {
      offset[k + -1] = k * bstride + ((6 - dir) * k) / 2;
    }
  }
  return;
}