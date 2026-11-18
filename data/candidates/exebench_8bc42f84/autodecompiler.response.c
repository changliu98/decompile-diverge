static int mpeg3video_calc_mv(int *mv, int mv_format, int h_r_size,
                         int v_r_size, int full_pel_vector)
{
  int lim, vec, vec1;
  int range = 16 << mv_format;

  if(full_pel_vector) vec = (*mv >> 1);
  else vec = *mv;

  vec1 = vec;

  if(h_r_size > 0)
  {
    vec1 += ((h_r_size - 1) << mv_format) + v_r_size + 1;

    if(vec1 >= range)
      vec1 -= range + range;
  }
  else if(h_r_size < 0)
  {
    vec1 -= ((-h_r_size - 1) << mv_format) + v_r_size + 1;

    if(vec1 < -range)
      vec1 += range + range;
  }

  if(full_pel_vector) lim = vec1 << 1;
  else lim = vec1;

  return (*mv = lim);
}