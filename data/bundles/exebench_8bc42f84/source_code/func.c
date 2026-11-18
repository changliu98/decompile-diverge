#include <stdio.h>

void mpeg3video_calc_mv(int *pred, int r_size, int motion_code, int motion_r, int full_pel_vector)
{
 int lim = 16 << r_size;
 int vec = full_pel_vector ? (*pred >> 1) : (*pred);

 if(motion_code > 0)
 {
     vec += ((motion_code - 1) << r_size) + motion_r + 1;
     if(vec >= lim) vec -= lim + lim;
 }
 else
 if(motion_code < 0)
 {
     vec -= ((-motion_code - 1) << r_size) + motion_r + 1;
     if(vec < -lim) vec += lim + lim;
 }
 *pred = full_pel_vector ? (vec << 1) : vec;
}
