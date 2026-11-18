void od_filter_dering_direction_offsets(od_coeff *offset, int dir,
 int bstride) {
  int k;
  if (dir <= 4) {
    for (k = 1; k < 4; k++) {
      offset[k - 1] = ((dir - 2) * k / 2) * bstride + k;
    }
  } else {
    for (k = 1; k < 4; k++) {
      offset[k - 1] = k * bstride + (6 - dir) * k / 2;
    }
  }
}