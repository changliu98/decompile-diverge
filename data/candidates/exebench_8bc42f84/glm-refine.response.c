void __cdecl mpeg3video_calc_mv(int *pred, int r_size, int motion_code, int motion_r, int full_pel_vector)
{
  int pred_scaled;
  int vec;
  int lim;

  // Calculate the motion vector limit based on the resolution size
  lim = 16 << r_size;

  // Scale the prediction vector if full-pel based, otherwise use as-is
  pred_scaled = full_pel_vector ? (*pred >> 1) : *pred;
  vec = pred_scaled;

  // Compute the new motion vector based on the motion code and residual
  if (motion_code > 0) {
    vec += motion_r + ((motion_code - 1) << r_size) + 1;
    if (vec >= lim)
      vec -= 2 * lim;
  } else if (motion_code < 0) {
    vec -= motion_r + ((-motion_code - 1) << r_size) + 1;
    if (vec < -lim)
      vec += 2 * lim;
  }

  // Scale back to full-pel resolution if necessary and store
  *pred = full_pel_vector ? (2 * vec) : vec;
}