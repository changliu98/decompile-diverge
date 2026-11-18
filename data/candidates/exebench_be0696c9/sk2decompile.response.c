float get_near_num(float num, float *p, float *near_num) {
  float near_num_tmp;
  if (p < near_num) {
    *near_num = *p;
    near_num_tmp = num;
  }
  return near_num_tmp;
}