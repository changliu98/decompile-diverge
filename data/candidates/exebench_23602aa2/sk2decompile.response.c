void lib3ds_quat_scalar(float c[4], float s) {
  int i;
  for (i = 0; i < 4; i++) {
    c[i] *= s;
  }
}