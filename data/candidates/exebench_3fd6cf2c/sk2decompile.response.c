void od_filter_dering_direction_offsets(int *offsets, int direction,
                                        int stride) {
  int i;
  if (direction < 5) {
    for (i = 1; i < 4; i++) {
      offsets[i - 1] = stride * i + (direction - 2) * i / 2;
    }
  } else {
    for (i = 1; i < 4; i++) {
      offsets[i - 1] = stride * i + (6 - direction) * i / 2;
    }
  }
}