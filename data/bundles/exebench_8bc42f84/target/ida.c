void __cdecl mpeg3video_calc_mv(int *pred, int r_size, int motion_code, int motion_r, int full_pel_vector)
{
  int v5; // [rsp+0h] [rbp-28h]
  int v6; // [rsp+4h] [rbp-24h]
  int vec; // [rsp+8h] [rbp-20h]
  int lim; // [rsp+Ch] [rbp-1Ch]

  lim = 16 << r_size;
  if ( full_pel_vector )
    v6 = *pred >> 1;
  else
    v6 = *pred;
  vec = v6;
  if ( motion_code <= 0 )
  {
    if ( motion_code < 0 )
    {
      vec = v6 - (motion_r + ((-motion_code - 1) << r_size) + 1);
      if ( vec < -lim )
        vec += 2 * lim;
    }
  }
  else
  {
    vec = v6 + motion_r + ((motion_code - 1) << r_size) + 1;
    if ( vec >= lim )
      vec -= 2 * lim;
  }
  if ( full_pel_vector )
    v5 = 2 * vec;
  else
    v5 = vec;
  *pred = v5;
}