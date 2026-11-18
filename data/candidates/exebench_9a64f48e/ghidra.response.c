int vis5d_color_table_set_alpha(float *params,float alpha)

{
  float alpha_local;
  float *params_local;
  
  params[3] = alpha;
  if (0.0 <= alpha) {
    params[5] = alpha;
    params[6] = alpha;
    params[3] = alpha;
  }
  else {
    params[5] = 0.0;
    params[6] = DAT_00102028;
    if (((double)alpha != DAT_00102008) || (NAN((double)alpha) || NAN(DAT_00102008))) {
      params[2] = DAT_0010202c;
    }
    else {
      params[2] = 0.0;
      params[3] = DAT_00102030;
    }
  }
  return 0;
}