static void mpeg3video_calc_mv(int *mv, int mvscale, int mvhor, int mvver,
                               int half_pel) {
  int mv_temp;
  int mv_out;
  int mv_max;
  mv_max = 16 << mvscale;
  if (half_pel)
    mv_temp = *mv >> 1;
  else
    mv_temp = *mv;
  mv_out = mv_temp;
  if (mvhor > 0) {
    mv_out += mvver + ((mvhor - 1) << mvscale) + 1;
    if (mv_out >= mv_max) mv_out -= 2 * mv_max;
  } else if (mvhor < 0) {
    mv_out -= mvver + ((-mvhor - 1) << mvscale) + 1;
    if (mv_out < -mv_max) mv_out += 2 * mv_max;
  }
  if (half_pel)
    mv_out <<= 1;
  else
    mv_out = mv_out;
  *mv = mv_out;
}