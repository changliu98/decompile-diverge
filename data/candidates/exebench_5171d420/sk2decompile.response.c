int inverse_rot(int *rot, int *rot_inv) {
  if (rot[1] == 0 || rot[2] == 0) return 1;
  rot_inv[0] = 0;
  rot_inv[1] = 1048576 / rot[2];
  rot_inv[2] = 1048576 / rot[1];
  rot_inv[3] = 0;
  rot_inv[4] = -rot[5] * rot_inv[2] / 1024;
  rot_inv[5] = -rot[4] * rot_inv[1] / 1024;
  return 0;
}