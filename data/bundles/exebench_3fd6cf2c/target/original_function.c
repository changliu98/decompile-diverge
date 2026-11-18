void od_filter_dering_direction_offsets(int *offset, int dir, int bstride) {
  int k;
  int f;
  if (dir <= 4) {
    f = dir - 2;
    for (k = 1; k <= 3; k++) offset[k - 1] = f*k/2*bstride + k;
  }
  else {
    f = 6 - dir;
    for (k = 1; k <= 3; k++) offset[k - 1] = k*bstride + f*k/2;
  }
}