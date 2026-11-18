void quant_u(float *u, int *qu, float u_min, float u_max, int qu_max) {
  int qu_tmp;
  float du, u_tmp;
  du = (u_max - u_min) / (float)(qu_max - 1);
  u_tmp = u_min + du * 0.5;
  for (qu_tmp = 0; qu_tmp < qu_max - 1; qu_tmp++) {
    if (u_tmp > *u) break;
    u_tmp += du;
  }
  *u = u_min + du * (float)qu_tmp;
  *qu = qu_tmp;
}